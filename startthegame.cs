using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class startthegame : MonoBehaviour
{
    public string x;
    Animator m_Animator;


    public STM32 stm_start;
    void Start()
    {
        m_Animator = GetComponent<Animator>();
    }

    void Update()
    {
      if ( stm_start.get_start() == 0 )
        {
            m_Animator.SetBool(x, true);
        }
    }

} 
