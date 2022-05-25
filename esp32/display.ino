const int lcdColumns=16;
const int lcdRows=2;
char lcdLines[lcdRows][lcdColumns];
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

bool __display_blink_prev=1;
bool __display_cursor_prev=1;
bool __display_back_prev=0;

bool __display_blink=0;
bool __display_cursor=0;
bool __display_back=1;

void display(const String& str){
	int x=0;
	int y=0;
	for(int i=0;i<str.length();++i){
		char c=str[i];
		if(c=='\n'){
			++y;
			x=0;
		}else{
			if(x<lcdColumns&&y<lcdRows){
				lcdLines[y][x]=c;
			}
			++x;
		}
	}
}

void display_set_blink(bool b){
	__display_blink=b;
}
void display_set_back(bool b){
	__display_back=b;
}
void display_set_cursor(bool c){
	__display_cursor=c;
}
void display_init(){
	lcd.init();
	lcd.backlight();
	for(int y=0;y<lcdRows;++y){
		for(int x=0;x<lcdColumns;++x){
			lcdLines[y][x]=' ';
		}
	}
	display_loop();
}
void display_loop(){
	if(__display_back!=__display_back_prev){
		if(__display_back){
			lcd.backlight();
		}else{
			lcd.noBacklight();
		}
		__display_back_prev=__display_back;
	}
	if(__display_blink!=__display_blink_prev){
		if(__display_blink){
			lcd.blink();
		}else{
			lcd.noBlink();
		}
		__display_blink_prev=__display_blink;
	}
	if(__display_cursor!=__display_cursor_prev){
		if(__display_cursor){
			lcd.cursor();
		}else{
			lcd.noCursor();
		}
		__display_cursor_prev=__display_cursor;
	}
	for(int i=0;i<lcdRows;++i){
		lcd.setCursor(0, i);
		lcd.printstr(lcdLines[i]);
	}
}
