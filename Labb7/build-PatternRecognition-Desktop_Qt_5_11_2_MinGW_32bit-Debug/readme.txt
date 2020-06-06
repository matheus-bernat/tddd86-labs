/**********************************************************************
 *  Mönsterigenkänning readme.txt
 **********************************************************************/

/**********************************************************************
 *  Empirisk    Fyll i tabellen nedan med riktiga körtider i sekunder
 *  analys      när det känns vettigt att vänta på hela beräkningen.
 *              Ge uppskattningar av körtiden i övriga fall.
 *
 **********************************************************************/
    
      N       brute[ms]    sortering[ms]
 ----------------------------------
    150	      52      	
    200       111  
    300       335  
    400       755  
    800       5837 
   1600       46552
   3200       372922
   6400	      2983376
  12800	      23867008


/**********************************************************************
 *  Teoretisk   Ge ordo-uttryck för värstafallstiden för programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute:  Denna metod har ordouttryck O(n⁴) för värsta fallet. Varje inre for-loop exekveras (N-3-i) gånger. Vi summerar
	c*(N-3-i)³ från i = 0 till i = N-3. Vi får alltså ordouttrcyket O(n⁴). 

Sortering: 
