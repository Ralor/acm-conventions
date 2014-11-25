/* 
    welcome.java
    Welcome, 2013 Mid-Central Programming Competition, Problem A
    Java Solution by Andy Harrington

    The program creates a map 
        pair: last initial -> set of all corresponding first initials
    An order in the set of last initials (allLast) is created to use them 
    with bitfields to generate all subsets of the possible last initials. 
    Process each such set of last initials:
       It sees which first initials must be used (when the last is not)
       Find the total number of first and last intials used
    The minimum of all the totals is output.
*/

import java.util.*;
import java.io.*;

public class welcome
{
    public static void main(String[] args) throws Exception {
        String file = (args.length > 0) ? args[0] : "welcome.in";
        Scanner in = new Scanner(new File(file));
        int dataset = 0; // judge
        int N = in.nextInt();
        while (N != 0) { 
            HashMap<Character, HashSet<Character>> pair =    // map: last -> 
                new HashMap<Character, HashSet<Character>>();//   set of first
            for (int i = 0; i < N; i++) {
                char s = in.next().charAt(0), t = in.next().charAt(0); 
                if (!pair.containsKey(t))                  // new last initial
                    pair.put(t, new HashSet<Character>()); //   so new entry
                pair.get(t).add(s);          // first initial in set for last
            }
            Character[] allLast = pair.keySet().toArray(new Character[0]);
            int nLast = allLast.length, low = nLast, nSets = (1 << nLast);
            for (int mask=0; mask < nSets; mask++) { // bit 1 -> last used
                HashSet<Character> firstUsed = new HashSet<Character>(); 
                int totGroups = 0;
                for (int i = 0; i < nLast; i++)    // combine first required
                    if ((mask & (1<<i)) == 0)      // i-th last not used
                        firstUsed.addAll(pair.get(allLast[i])); 
                    else 
                        totGroups++;       // is group for that last initial
                totGroups += firstUsed.size(); 
                if (totGroups < low) low = totGroups;           
            }
            System.out.println(low);
            N = in.nextInt();
            if (++dataset > 20) System.err.println("Too may datasets");
        }
    }
}  
