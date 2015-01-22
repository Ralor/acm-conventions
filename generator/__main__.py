import argparse
import cogapp
import contextlib
import io
import os
import os.path
import random
import shlex
import shutil
import sys
import tempfile

guid = None
projects = None
local = None

def problem_number(s):
    try:
        n = int(s)
        if 0 < n <= 26:
            return n - 1
    except ValueError:
        with contextlib.suppress(TypeError):
            n = ord(s.upper()) - ord('A')
            if 0 <= n < 26:
                return n
    raise argparse.ArgumentTypeError("invalid problem number: %r" % s)

def ensure_existance(filename):
    if not os.path.exists(filename):
        raise FileNotFoundError(filename)
    return filename

def get_alph_char(i):
    return str(i) if 0 <= i <= 9 else chr(ord('A') + i - 10)

# 8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942
def generate_guid():
    s = io.StringIO()
    for i in range(8):
        s.write(get_alph_char(random.randrange(36)))
    s.write('-')
    for i in range(3):
        for j in range(4):
            s.write(get_alph_char(random.randrange(36)))
        s.write('-')
    for i in range(12):
        s.write(get_alph_char(random.randrange(36)))
    return s.getvalue()

@contextlib.contextmanager
def temp_file():
    try:
        fd, name = tempfile.mkstemp(text=True)
        f = os.fdopen(fd, "w")
        yield f, name
    finally:
        f.close()
        os.remove(name)

def main():
    global guid, projects, local

    parser = argparse.ArgumentParser(fromfile_prefix_chars="@")
    parser.add_argument("--solution-name", metavar="NAME")
    parser.add_argument("--last-problem", type=problem_number, metavar="ALNUM", help="""
        can be either alphabetical letter or number
    """)
    parser.add_argument("--cog", nargs=argparse.REMAINDER, default=[ ], help="""
        custom arguments that are passed to Cog
    """)
    parser.add_argument("solution", type=ensure_existance)
    parser.add_argument("vcxproj", type=ensure_existance)
    parser.add_argument("vcxproj_filters", type=ensure_existance, metavar="vcxproj-filters")
    parser.add_argument("source", type=ensure_existance)
    parser.add_argument("project_name", metavar="project-name")
    parser.add_argument("source_name", metavar="source-name")
    parser.add_argument("input_name", metavar="input-name")
    parser.add_argument("local", help="""
        local project definition
    """)
    parser.add_argument("definitions", type=ensure_existance)

    args = parser.parse_args()

    if args.solution_name is None:
        args.solution_name = input("Solution name: ")
    if args.last_problem is None:
        args.last_problem = problem_number(input("Last problem: "))

    local = args.local
    custom = ' '.join(map(shlex.quote, args.cog))

    try:
        os.mkdir(args.solution_name)
    except FileExistsError:
        for e in os.listdir(args.solution_name):
            entry = os.path.join(args.solution_name, e)
            if os.path.isdir(entry):
                shutil.rmtree(entry)
            elif os.path.isfile(entry):
                os.remove(entry)

    definitions = [ ]
    with open(args.definitions) as f:
        for line in f:
            line = line.strip()
            if not line.startswith((';', '#', "//")) and '=' in line:
                definitions.append(line)

    projects = [ ]
    with temp_file() as (cog_cmd, cog_cmd_name):
        for i in range(args.last_problem + 1):
            d = {
                "upper": chr(ord('A') + i),
                "lower": chr(ord('a') + i),
                "number": str(i + 1),
                "number0": str(i),
                "local": local,
            }
            name = args.project_name.format_map(d)
            g = generate_guid()
            path = os.path.join(args.solution_name, name)
            with contextlib.suppress(FileExistsError):
                os.mkdir(path)
            input_name = args.input_name.format_map(d)
            with open(os.path.join(path, input_name), "w") as f:
                print(file=f)
            source_name = args.source_name.format_map(d)
            s = io.StringIO()
            for kv in definitions:
                s.write(" -D")
                s.write(kv.format_map(d))
            print("%s %s%s -o'%s'" % (
                args.source, custom, s.getvalue(), os.path.join(path, source_name)
            ), file=cog_cmd)
            s = os.path.join(path, name + ".vcxproj")
            print("%s %s -Dname=%s -Dguid=%s -Dsource_file='%s' -Dinput_file='%s' -o'%s'" % (
                args.vcxproj, custom, name, g, source_name, input_name, s
            ), file=cog_cmd)
            s = os.path.join(path, name + ".vcxproj.filters")
            print("%s %s -Dsource_file='%s' -Dinput_file='%s' -o'%s'" % (
                args.vcxproj_filters, custom, source_name, input_name, s
            ), file=cog_cmd)
            projects.append(dict(name=name, guid=g))

        guid = generate_guid()
        print("%s %s -o'%s'" % (
            args.solution, custom, os.path.join(args.solution_name, args.solution_name + ".sln")
        ), file=cog_cmd)

        cog_cmd.flush()
        cogapp.Cog().main(sys.argv[:1] + shlex.split(custom) + ["-de", '@' + cog_cmd_name])

if __name__ == "__main__":
    main()
