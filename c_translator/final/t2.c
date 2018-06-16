//nested for loop

int f(int x, int y)
{ 
  int i = 0;
  int j = 0;
  int k = 0;
  for(i = 8; i < 10; i++){
	for(j = 8; j < 10; j++){
		for(k = 8; k < 10; k++){
			x++;
		}
		y++;
	}  
  }
  return x + y;
}

int main(){
	int x = 0;
	int y = 0;
	
	return f(x,y);
}