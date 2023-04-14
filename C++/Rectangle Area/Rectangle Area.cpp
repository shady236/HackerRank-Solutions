
/*
 * Create classes Rectangle and RectangleArea
 */
class Rectangle
{
    public:
    int widrh, height;
    
    void display()
    {
        cout << widrh << " " << height << endl;
    }
};

class RectangleArea : public Rectangle
{
    public:
    
    void read_input()
    {
        cin >> widrh >> height;
    }
    
    void display()
    {
        cout << widrh * height << endl;
    }
};

