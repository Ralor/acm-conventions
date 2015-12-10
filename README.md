acm-conventions
=========

"NppExec" commands:

C++11 compile & run (debug)

```

NPP_SAVE
cmd /c cd "$(CURRENT_DIRECTORY)" && g++ -std=c++11 -g -Wall -Wextra -pedantic -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wcast-qual -Wcast-align -Wno-unused-result -Wno-unused-parameter -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -DLOCAL_PROJECT -DLOCAL_DEBUG -o "$(NAME_PART).exe" "$(FULL_CURRENT_PATH)" && "$(NAME_PART).exe" <"$(NAME_PART).in"

```

C++11 compile & run (release)

```

NPP_SAVE
cmd /c cd "$(CURRENT_DIRECTORY)" && g++ -std=c++11 -O2 -DLOCAL_PROJECT -o "$(NAME_PART).exe" "$(FULL_CURRENT_PATH)" && "$(NAME_PART).exe" <"$(NAME_PART).in"

```

Kill app

```

NPP_SAVE
cmd /c taskkill /f /IM "$(NAME_PART).exe"

```