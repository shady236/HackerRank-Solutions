

//Write your code here
class Add {
    
    public void add(int ... a){
        int sum = 0;
        for(int i = 0; i < a.length - 1; i++)
        {
            sum += a[i];
            System.out.print(a[i] + "+");
        }
        
        sum += a[a.length - 1];
        System.out.println(a[a.length - 1] + "=" + sum);
    }
    
}


