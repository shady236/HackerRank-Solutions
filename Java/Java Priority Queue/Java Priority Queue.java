
import java.util.*;

/*
 * Create the Student and Priorities classes here.
 */

class Student 
{
    private int id;
    private String name;
    private double CGPA;
    
    public Student(int id, String name, double CGPA) {
        this.id = id;
        this.name = name;
        this.CGPA = CGPA;
    }
    
    public int getId() {
        return id;
    }
    
    public String getName() {
        return name;
    }
    
    public double getCGPA() {
        return CGPA;
    }
}

class studentsComparator implements Comparator<Student>
{
    
    @Override
    public int compare(Student o1, Student o2)
    {
        if(o1.getCGPA() > o2.getCGPA())
            return -1;
        if(o1.getCGPA() < o2.getCGPA())
            return 1;
        
        int x = o1.getName().compareTo(o2.getName());
        if(x != 0)
            return x;
        
        return o2.getId() - o1.getId();
    }
    
}

class Priorities 
{
    
    PriorityQueue<Student> studentsQu;
    
    public Priorities()
    {
        studentsQu = new PriorityQueue<>(new studentsComparator());
    }
    
    public List<Student> getStudents(List<String> events)
    {
        for(String str : events) 
        {
            String[] event = str.split(" ");
            
            if(event[0].equals("SERVED"))
                studentsQu.poll();
            else 
                studentsQu.add(new Student(
                    Integer.parseInt(event[3]), 
                    event[1], 
                    Double.parseDouble(event[2]))
                );
        }
        
        List<Student> ret = new ArrayList<>(studentsQu);
        Collections.sort(ret, new studentsComparator());
        return ret;
    }
}

