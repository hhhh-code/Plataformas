bool Rango(float Begin,float End, float Point){
	return Point >= Begin and Point <= End;
}

void draw_text(BITMAP* bmp, int x, int y, int color, const char* text){
	textprintf_ex(bmp, font, x, y, color, -1, "%s", text);
}

void draw_text(BITMAP* bmp, int x, int y, int w, int color, string text){
	int _x = 0;
	int _y = 0;
	
	
	for(int i = 0; i < text.length(); i++){
		
		if(text.at(i) == ' '){
			int len = 0;
			for(int e = i+1; e < text.length(); e++){
				len++;
				if(text.at(e) == ' ') break;
			}
			
			if((_x+len)*8 >= w){
				_x = 0;
				_y++;
				i++;
			}
		}
		
		if(_x*8 >= w){
			_x = 0;
			_y++;
		}
		
		textprintf_ex(bmp, font, x+(_x*8), y+(_y*9), color, -1, "%c", text.at(i));
		_x++;
	}	
}

