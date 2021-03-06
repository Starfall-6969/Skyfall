
Федеральное государственное автономное образовательное учреждение высшего образования  

"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"  

ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ  

Кафедра компьютерной инженерии и моделирования
<br/></br>



### Отчет по лабораторной работе №3 </br> по дисциплине "Программирование"
<br/>

Студента 1 курса группы ИВТ-б-о-191(1)  
Гринь Татьяны Станиславовны </br>
направления подготовки 09.03.01 " Информатика и вычислительная техника"  
<br/>

<table>
<tr><td>Научный руководитель<br/> старший преподаватель кафедры<br/> компьютерной инженерии и моделирования</td>
<td>(оценка)</td>
<td>Чабанов В.В.</td>
</tr>
</table>
<br/><br/>
​
Симферополь, 2019

__Цель:__ <br>
+ Закрепить навыки разработки программ использующих операторы цикла;
+ Закрепить навыки разработки программ использующих массивы;
+ Освоить методы подключения сторонних библиотек.

__Постановка задачи:__<br>
+ Напишите на языке С++ программу, которая по заданному изображению и ключу восстанавливает исходное текстовое сообщение (Си-строка) зашифрованное в изображении.

__Ход работы:__ 

__1.__ __Исходное изображение и ключ:__

![](http://cpp.codelearn.ru/lab/lab3pic/pic1.bmp)
<br> 
Рисунок 1. Изображение, с которого будет декодироваться текст. <br> 

![](https://raw.githubusercontent.com/Starfall-6969/Skyfall/master/%D0%9B%D0%B0%D0%B1%D0%BE%D1%80%D0%B0%D1%82%D0%BE%D1%80%D0%BD%D0%B0%D1%8F%203/%D0%A1%D0%BA%D0%B8%D1%80%D0%B8%D0%BD%D1%88%D0%BE%D1%82%D1%8B/%D0%9A%D0%B8%D0%BB%D1%8E%D1%87.PNG) <br> 

Рисунок 2. Ключ, по которому кодировался/декодировался текст.<br> 

__2.__ __Код программы для декодирования сообщения:__
```c++
#include <iostream>
#include <bitset>
#include <climits>
#include "libbmp.h"


char bit(int x,int y,int k,int b, BmpImg img) { 
  char a;
  if (k == 0) {
    a=img.red_at(x, y);
  }
  else if (k == 1) {
    a=img.green_at(x, y);
  }
  else if (k == 2) {
    a=img.blue_at(x, y);
  }
  a = a & (~((1 << 1) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7))); // обнуление первых 7ми битов
  a = (a << b); //sdvig
  return a;
}
using namespace std; 
int main()
{
  BmpImg img;
  string message;
  char symb = 0;// переменная для хранения символов

  int b = 7; //sdvigi
  bool flag = true;
  img.read("pic1.bmp");

  for (int y = 0; y < 627; y++) {  
    for (int x = 0; x < 600; x++) { 

      for (int k = 0; k < 3; k++) { //смена канала

        if (b < 0) { //сдвги
          b = 7;  
          message += symb;  

           if (symb == 0)  //заверш текста
           { flag = false; break; }

        cout << symb; 
        symb = 0; 
        }
        symb += bit(599 - x, 626 - y, k, b, img);
        b--;
      }
      if (flag == false) { break; }
    }
    if (flag == false) { break; }
  }
}
```
__3.__ __Декодрованное сообщение:__ <br> 

George Washington (February 22, 1732[b][c] Ц December 14, 1799) was an American political leader, military general, statesman, and Founding Father who served as the first president of the United States from 1789 to 1797. Previously, he led Patriot forces to victory in the nation's War for Independence. He presided at the Constitutional Convention of 1787 which established the U.S. Constitution and a federal government. Washington has been called the "Father of His Country" for his manifold leadership in the formative days of the new nation.
Washington received his initial military training and command with the Virginia Regiment during the French and Indian War. He was later elected to the Virginia House of Burgesses and was named a delegate to the Continental Congress, where he was appointed Commanding General of the Continental Army. He commanded American forces, allied with France, in the defeat and surrender of the British during the Siege of Yorktown, and resigned his commission in 1783 after the signing of the Treaty of Paris.
Washington played a key role in the adoption and ratification of the Constitution and was then elected president by the Electoral College in the first two elections. He implemented a strong, well-financed national government while remaining impartial in a fierce rivalry between cabinet members Thomas Jefferson and Alexander Hamilton. During the French Revolution, he proclaimed a policy of neutrality while sanctioning the Jay Treaty. He set enduring precedents for the office of president, including the title "President of the United States", and his Farewell Address is widely regarded as a pre-eminent statement on republicanism.
Washington owned slaves for labor and trading, and supported measures passed by Congress protecting slavery, in order to preserve national unity. He later became troubled with the institution of slavery and freed his slaves in a 1799 will. He endeavored to assimilate Native Americans into Western culture, but responded to their hostility in times of war. He was a member of the Anglican Church and the Freemasons, and he urged broad religious freedom in his roles as general and president. Upon his death, he was eulogized as "first in war, first in peace, and first in the hearts of his countrymen." He has been memorialized by monuments, art, geographical locations, stamps, and currency, and many scholars and polls rank him among the greatest American presidents.<br> 

**Вывод**<br> 

В ходе выполнения лабораторной работы были закреплены навыки разработки программ использующих операторы цикла, разработки программ использующих массивы. Освоены методы подключения сторонних библиотек. 
