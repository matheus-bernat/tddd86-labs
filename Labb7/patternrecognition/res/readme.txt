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
    150	      52      	   91
    200       111          130
    300       335          265
    400       755          466
    800       5837         1655
   1600       46552        5971
   3200       372922       23045
   6400	      2983376      92180
  12800	      23867008     368720


/**********************************************************************
 *  Teoretisk   Ge ordo-uttryck för värstafallstiden för programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute:  Denna metod har ordouttryck O(n⁴) för värsta fallet. Varje inre for-loop exekveras (N-3-i) gånger. Vi summerar
	c*(N-3-i)³ från i = 0 till i = N-3. Vi får alltså ordouttrcyket O(n⁴). 

Sortering: Denna metod har ordouttryck O(n^2*log(n)) för värsta fallet. Vi har två inre for-loopar som körs efter varandra N gånger
           och en yttre som körs N gånger. Dessutom har vi uppslagningstid på mapen som log(n). Då får vi ordouttrycket O(n^2*log(n)).
