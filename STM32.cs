using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Threading; 
using System.IO.Ports;


public class STM32 : MonoBehaviour
{
  public  int start1 = 9 ;
    int serial_data;

    SerialPort sp = new SerialPort("COM6", 9600);
    int x , y , z ;
    void Start()
    {
       sp.Open();
    }

    void Update()
    {
        var toRead1 = sp.BytesToRead ;  
        if (sp.IsOpen && toRead1 > 0 )
        {
            serial_data = sp.ReadByte();
            try
            {
                switch (serial_data)
            {
                    case 0:
                        start1 = 0;
                        break;
                    case 1:
                        while (sp.BytesToRead == 0) ;
                        x = sp.ReadByte();
                        break;
                    case 2:                      
                        while (sp.BytesToRead == 0) ;
                        y = sp.ReadByte();                    
                        break;
                    case 3:
                        while (sp.BytesToRead == 0) ;
                        z = sp.ReadByte();
                        break;
                    default:
                        break;
            }
           
         
            }
            catch (System.Exception)
            {
                Debug.Log("Error!");
            }
        }
        print("the 1 value " + y);

        print("the 2 value "+ x);

        print("the 3 value " + z);

    }
    public int get_start()
    {
        return start1;
    }
    public int sens_1()
    {
        return y;
    }
    public int sens_2()
    {
        return x;
    }
    public int sens_3()
    {
        return z;
    }

}