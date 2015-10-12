#include"My_method.hpp"

//! 挿入ソート
// 明解C言語によるアルゴリズムとデータ構造P167
void insertion(double a[], int n)
{
    for (int i=1; i <n; i++)
    {
        int j;
        int tmp = a[i];
        for (j=i; j>0 && a[j-1]> tmp; j--)
        {
            a[j] = a[j-1];
        }
        a[j] = tmp;
    }
}

//0～π 
//-π ～π までの範囲に変換
double changeAngle(double source)
{
	if(source > M_PI)
	{
		return source - M_PI*2.0;
	}
	else if(source <= -M_PI)
	{
		return M_PI*2.0 + source;
	}
	else
		return source;
}



//文字を数字に変換
int ChangeCharacter(int *i, unsigned char c)
{
	if(c == '0') {	*i = 0;	}
	else if(c == '1') {	*i = 1;	}
	else if(c == '2') {	*i = 2;	}
	else if(c == '3') {	*i = 3;	}
	else if(c == '4') {	*i = 4;	}
	else if(c == '5') {	*i = 5;	}
	else if(c == '6') {	*i = 6;	}
	else if(c == '7') {	*i = 7;	}
	else if(c == '8') {	*i = 8;	}
	else if(c == '9') {	*i = 9;	}
	else if(c == 'A') {	*i = 0x0a;}
	else if(c == 'B') {	*i = 0x0b;}
	else if(c == 'C') {	*i = 0x0c;}
	else if(c == 'D') {	*i = 0x0d;}
	else if(c == 'E') {	*i = 0x0e;}
	else if(c == 'F') {	*i = 0x0f;}
	else {*i = 0;}

	return 0;
}

//数字を文字に変換
int ChangeFigure(int i, unsigned char *c)
{
	if(i == 0) {	*c = '0';	}
	else if(i == 1) {	*c = '1';	}
	else if(i == 2) {	*c = '2';	}
	else if(i == 3) {	*c = '3';	}
	else if(i == 4) {	*c = '4';	}
	else if(i == 5) {	*c = '5';	}
	else if(i == 6) {	*c = '6';	}
	else if(i == 7) {	*c = '7';	}
	else if(i == 8) {	*c = '8';	}
	else if(i == 9) {	*c = '9';	}	
	else if(i == 0x0a) {	*c = 'A';	}	
	else if(i == 0x0b) {	*c = 'B';	}	
	else if(i == 0x0c) {	*c = 'C';	}	
	else if(i == 0x0d) {	*c = 'D';	}	
	else if(i == 0x0e) {	*c = 'E';	}	
	else if(i == 0x0f) {	*c = 'F';	}	
	else {*c = '0';}

	return 0;
}
 
double getETime(void)
{
	struct timeval tv;
   	gettimeofday(&tv, NULL);
	return tv.tv_sec + (double)tv.tv_usec*1e-6;
}
