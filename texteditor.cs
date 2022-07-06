using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
public class texteditor : MonoBehaviour
{
   public Text harf ;
    public STM32 stm_analog;

    void Start()
    {
        bool finger_1_down = stm_analog.sens_1() > 30 && stm_analog.sens_1() < 100;
        bool finger_1_up = stm_analog.sens_1() < 30;

        bool finger_2_down = stm_analog.sens_2() > 30 && stm_analog.sens_2() < 100;
        bool finger_2_up = stm_analog.sens_2() < 30;

        bool finger_3_down = stm_analog.sens_3() > 30 && stm_analog.sens_3() < 100;
        bool finger_3_up = stm_analog.sens_3() < 30;

    }
    void Update()
    {
        if (stm_analog.sens_1() > 30 && stm_analog.sens_1() < 100
           && stm_analog.sens_2() > 30 && stm_analog.sens_2() < 100
            && stm_analog.sens_3() > 30 && stm_analog.sens_3() < 100
            )
        {
            harf.text = "A";
        }


        else if (stm_analog.sens_1() < 30
           && stm_analog.sens_2() > 30 && stm_analog.sens_2() < 100
            && stm_analog.sens_3() > 30 && stm_analog.sens_3() < 100
            )
        {
            harf.text = "D";
        }

        else if (stm_analog.sens_1() < 30 
          && stm_analog.sens_2() < 30 
           && stm_analog.sens_3() > 30 && stm_analog.sens_3() < 100
           )
        {
            harf.text = "V";
        }
        else
        {
            harf.text = " ";


        }

    }
}
