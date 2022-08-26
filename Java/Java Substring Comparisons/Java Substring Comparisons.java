

    public static String getSmallestAndLargest(String s, int k) {
        String smallest = "";
        String largest = "";
        
        // Complete the function
        // 'smallest' must be the lexicographically smallest substring of length 'k'
        // 'largest' must be the lexicographically largest substring of length 'k'
        
        largest  = s.substring(0, k);
        smallest = largest + "";
        
        for (int i = 0; i <= s.length() - k; i++) 
        {
            String str = s.substring(i, i + k);
            
            if(largest.compareTo(str) < 0)
                largest = str;
            else if(smallest.compareTo(str) > 0)
                smallest = str;
        }
        
        return smallest + "\n" + largest;
    }

