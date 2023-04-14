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
     * Complete the 'runningMedian' function below.
     *
     * The function is expected to return a DOUBLE_ARRAY.
     * The function accepts INTEGER_ARRAY a as parameter.
     */

    public static List<Double> runningMedian(List<Integer> a)
    {
        List<Double>  res = new ArrayList<>(a.size());
        
        res.add((double) a.get(0));
        if(a.size() == 1)
            return res;
        
        res.add(((double) a.get(0) + a.get(1)) / 2.0);
        
        PriorityQueue<Integer> minHeap = new PriorityQueue<>(new Comparator<Integer>() {
            @Override
            public int compare(Integer o1, Integer o2) {
                return o1 - o2;
            }
        });
         
        PriorityQueue<Integer> maxHeap = new PriorityQueue<>(new Comparator<Integer>() {
            @Override
            public int compare(Integer o1, Integer o2) {
                return o2 - o1;
            }
        }); 
        
        if(a.get(0) < a.get(1))
        {
            maxHeap.add(a.get(0));
            minHeap.add(a.get(1));
        }
        else 
        {
            maxHeap.add(a.get(1));
            minHeap.add(a.get(0));
        }
        
        for(int i = 2; i < a.size(); i++)
        {
            if(a.get(i) <= minHeap.peek())
                maxHeap.add(a.get(i));
            else if(a.get(i) >= maxHeap.peek())
                minHeap.add(a.get(i));
            
            if(maxHeap.size() >= minHeap.size() + 2)
                minHeap.add(maxHeap.poll());
            else if(minHeap.size() >= maxHeap.size() + 2)
                maxHeap.add(minHeap.poll());
            
            if(i % 2 == 0)
            {
                if(maxHeap.size() > minHeap.size())
                    res.add((double) maxHeap.peek());
                else 
                    res.add((double) minHeap.peek());
            }
            else 
            {
                res.add(((double) maxHeap.peek() + minHeap.peek()) / 2.0);
            }
        }
        
        return res;
    }

}

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        int aCount = Integer.parseInt(bufferedReader.readLine().trim());

        List<Integer> a = IntStream.range(0, aCount).mapToObj(i -> {
            try {
                return bufferedReader.readLine().replaceAll("\\s+$", "");
            } catch (IOException ex) {
                throw new RuntimeException(ex);
            }
        })
            .map(String::trim)
            .map(Integer::parseInt)
            .collect(toList());

        List<Double> result = Result.runningMedian(a);

        bufferedWriter.write(
            result.stream()
                .map(Object::toString)
                .collect(joining("\n"))
            + "\n"
        );

        bufferedReader.close();
        bufferedWriter.close();
    }
}
