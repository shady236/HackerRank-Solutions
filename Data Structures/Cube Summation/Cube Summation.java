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
     * Complete the 'cubeSum' function below.
     *
     * The function is expected to return an INTEGER_ARRAY.
     * The function accepts following parameters:
     *  1. INTEGER n
     *  2. STRING_ARRAY operations
     */

    public static List<Long> cubeSum(int n, List<String> operations) {
        // Write your code here
        HashMap<Integer, Integer> cells = new HashMap<>();
        
        List<Long> res = new ArrayList<>();
        
        for (String op : operations) {
            
            String[] opFields = op.split(" ");
            
            if(opFields[0].equals("UPDATE"))
            {
                int x = Integer.parseInt(opFields[1]) - 1;
                int y = Integer.parseInt(opFields[2]) - 1;
                int z = Integer.parseInt(opFields[3]) - 1;
                int w = Integer.parseInt(opFields[4]);
                
                int key = x + y * 100 + z * 10000;
                
                if(cells.containsKey(key))
                    cells.replace(key, w);
                else 
                    cells.put(key, w);
            }
            else 
            {
                int x1 = Integer.parseInt(opFields[1]) - 1;
                int y1 = Integer.parseInt(opFields[2]) - 1;
                int z1 = Integer.parseInt(opFields[3]) - 1;
                
                int x2 = Integer.parseInt(opFields[4]) - 1;
                int y2 = Integer.parseInt(opFields[5]) - 1;
                int z2 = Integer.parseInt(opFields[6]) - 1;
                
                long sum = 0;
                for (Integer key : cells.keySet()) {
                    int x = key % 100;
                    int y = (key / 100) % 100;
                    int z = (key / 10000);
                    
                    if(x >= x1 && x <= x2 && y >= y1 && y <= y2 && z >= z1 && z <= z2)
                        sum += cells.get(key);
                }
                
                res.add(sum);
            }
        }
        
        return res;
    }

}

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        int T = Integer.parseInt(bufferedReader.readLine().trim());

        IntStream.range(0, T).forEach(TItr -> {
            try {
                String[] firstMultipleInput = bufferedReader.readLine().replaceAll("\\s+$", "").split(" ");

                int matSize = Integer.parseInt(firstMultipleInput[0]);

                int m = Integer.parseInt(firstMultipleInput[1]);

                List<String> ops = IntStream.range(0, m).mapToObj(i -> {
                    try {
                        return bufferedReader.readLine();
                    } catch (IOException ex) {
                        throw new RuntimeException(ex);
                    }
                })
                    .collect(toList());

                List<Long> res = Result.cubeSum(matSize, ops);

                bufferedWriter.write(
                    res.stream()
                        .map(Object::toString)
                        .collect(joining("\n"))
                    + "\n"
                );
            } catch (IOException ex) {
                throw new RuntimeException(ex);
            }
        });

        bufferedReader.close();
        bufferedWriter.close();
    }
}
