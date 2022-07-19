

        //Write your code here
        for(int i=0; i<s.length - 3; i++)
        {
            int idxOfMax = i;
            for(int j=i+1; j<s.length - 2; j++)
            {
                BigDecimal currMax = new BigDecimal(s[idxOfMax]);
                BigDecimal currNum = new BigDecimal(s[j]);
                
                if(currNum.compareTo(currMax) > 0)
                    idxOfMax = j;
            }
            String temp = s[i];
            s[i] = s[idxOfMax];
            s[idxOfMax] = temp;
        }
        
