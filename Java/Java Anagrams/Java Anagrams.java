

    static boolean isAnagram(String a, String b) 
    {
        // Complete the function
        int[] frequency = new int[26];
        
        int aLen = a.length();
        int bLen = b.length();
        
        for(int i=0; i<aLen; i++)
        {
            frequency[(a.charAt(i) & 0x5F) - 'A']++;
        }
        
        for(int i=0; i<bLen; i++)
        {
            frequency[(b.charAt(i) & 0x5F) - 'A']--;
        }
        
        for(int i=0; i<26; i++)
        {
            if(frequency[i] != 0)
            {
                return false;
            }
        }
        return true;
        
        
        
        
    }

