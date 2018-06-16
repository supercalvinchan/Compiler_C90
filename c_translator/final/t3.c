//while & comparison operator

int f(int x, int y){
	int tmp = x;
	while(x <= y){
		x += tmp;
	}
	return x;
}
int main(){
	int x = 3;
	int y = 100;
	return f(x,y);
}