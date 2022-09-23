import java.io.*;
import java.math.*;
import java.security.*;
import java.text.*;
import java.util.*;
import java.util.concurrent.*;
import java.util.function.*;
import java.util.regex.*;
import java.util.stream.*;
import static java.util.stream.Collectors.joining;
import static java.util.stream.Collectors.toList;

class Result {

    /*
     * Complete the 'intervalSelection' function below.
     *
     * The function is expected to return an INTEGER.
     * The function accepts 2D_INTEGER_ARRAY intervals as parameter.
     */

    public static int intervalSelection(List<List<Integer>> intervals) {
        // Write your code here
        
        Collections.sort(intervals, new Comparator<List<Integer>>() {
            @Override
            public int compare(List<Integer> o1, List<Integer> o2) {
                return o1.get(1) - o2.get(1);   //sort according to end time
            }
        });
        
        int cnt = 0;
        
        /* 
         * at most, two intervals can overlap
         * keep traking of end of these two intervals 
         */
        int intervalsEnd[] = new int[2];
        
        for(List<Integer> intv : intervals)
        {
            int strt = intv.get(0);
            int end  = intv.get(1);
            
            if(strt > intervalsEnd[0])
            {
                cnt++;
                intervalsEnd[0] = end;
            }
            else if(strt > intervalsEnd[1])
            {
                cnt++;
                intervalsEnd[1] = end;
                
                if(intervalsEnd[1] > intervalsEnd[0])
                {
                    int tmp = intervalsEnd[0];
                    intervalsEnd[0] = intervalsEnd[1];
                    intervalsEnd[1] = tmp;
                }
            }
        }
        
        return cnt;
    }

}

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        int s = Integer.parseInt(bufferedReader.readLine().trim());

        IntStream.range(0, s).forEach(sItr -> {
            try {
                int n = Integer.parseInt(bufferedReader.readLine().trim());

                List<List<Integer>> intervals = new ArrayList<>();

                IntStream.range(0, n).forEach(i -> {
                    try {
                        intervals.add(
                            Stream.of(bufferedReader.readLine().replaceAll("\\s+$", "").split(" "))
                                .map(Integer::parseInt)
                                .collect(toList())
                        );
                    } catch (IOException ex) {
                        throw new RuntimeException(ex);
                    }
                });

                int result = Result.intervalSelection(intervals);

                bufferedWriter.write(String.valueOf(result));
                bufferedWriter.newLine();
            } catch (IOException ex) {
                throw new RuntimeException(ex);
            }
        });

        bufferedReader.close();
        bufferedWriter.close();
    }
}
