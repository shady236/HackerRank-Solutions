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
     * Complete the 'minimumAverage' function below.
     *
     * The function is expected to return an INTEGER.
     * The function accepts 2D_INTEGER_ARRAY customers as parameter.
     */

    public static long minimumAverage(List<List<Integer>> customers)
    {
        Collections.sort(customers, new Comparator<List<Integer>>() {
            @Override
            public int compare(List<Integer> o1, List<Integer> o2) {
                return o1.get(0) - o2.get(0);   //order acording to tirst arriving
            }
        });
        
        PriorityQueue<List<Integer>> queue = new PriorityQueue<>(new Comparator<List<Integer>>() {
            @Override
            public int compare(List<Integer> o1, List<Integer> o2) {
                return o1.get(1) - o2.get(1);   //order acording to min serving time
            }
        });
        queue.add(customers.get(0));
        
        int idx = 1;
        BigInteger delays = BigInteger.ZERO;
        BigInteger t = BigInteger.valueOf(customers.get(0).get(0));
        while(!queue.isEmpty())
        {
            List<Integer> top = queue.poll();
            t = t.add(BigInteger.valueOf(top.get(1)));
            delays = delays.add(t.subtract(BigInteger.valueOf(top.get(0))));
            
            if(queue.isEmpty() && idx < customers.size() && BigInteger.valueOf(customers.get(idx).get(0)).compareTo(t) > 0)
            {
                t = BigInteger.valueOf(customers.get(idx).get(0));
            }
            
            
            while(idx < customers.size() && BigInteger.valueOf(customers.get(idx).get(0)).compareTo(t) <= 0)
            {
                queue.add(customers.get(idx));
                idx++;
            }
        }
        
        
        return (delays.divide(BigInteger.valueOf(customers.size())).longValue());
    }

}

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        int n = Integer.parseInt(bufferedReader.readLine().trim());

        List<List<Integer>> customers = new ArrayList<>();

        IntStream.range(0, n).forEach(i -> {
            try {
                customers.add(
                    Stream.of(bufferedReader.readLine().replaceAll("\\s+$", "").split(" "))
                        .map(Integer::parseInt)
                        .collect(toList())
                );
            } catch (IOException ex) {
                throw new RuntimeException(ex);
            }
        });

        long result = Result.minimumAverage(customers);

        bufferedWriter.write(String.valueOf(result));
        bufferedWriter.newLine();

        bufferedReader.close();
        bufferedWriter.close();
    }
}
