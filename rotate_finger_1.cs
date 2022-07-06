using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class rotate_finger_1: MonoBehaviour
{
    public STM32 stm_analog ;

    void Start()
    {
        
    }

    void FixedUpdate()
    {
      
        Vector3 eulerRotation = transform.rotation.eulerAngles;
        if (stm_analog.sens_1() > 30 && stm_analog.sens_1() <100 )
        {
            transform.rotation = Quaternion.Euler(eulerRotation.x, eulerRotation.y,
                80f);
        }
        else if (stm_analog.sens_3() > 0 && stm_analog.sens_3() < 30)
        {

            transform.rotation = Quaternion.Euler(eulerRotation.x, eulerRotation.y,
                    0f);
            
        }

    }
    public int scale(int OldMin, int OldMax, int NewMin, int NewMax, int OldValue)
    {

        int OldRange = (OldMax - OldMin);
        int NewRange = (NewMax - NewMin);
        int NewValue = (((OldValue - OldMin) * NewRange) / OldRange) + NewMin;

        return (NewValue);
    }
}
