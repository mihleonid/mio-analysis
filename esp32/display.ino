const int lcdColumns=16;
const int lcdRows=2;
char lcdLines[lcdRows][lcdColumns];
char lcdLines_prev[lcdRows][lcdColumns];
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

bool __display_blink_prev=1;
bool __display_cursor_prev=1;
bool __display_back_prev=0;
long __display_prev;

bool __display_blink=0;
bool __display_cursor=0;
bool __display_back=1;

bool __diff(char* a, char* b, int len){
	bool mark=0;
	for(int i=0;i<len;++i){
		if(a[i]!=b[i]){
			b[i]=a[i];
			mark=1;
		}
	}
	return mark;
}

void display_clear(){
	for(int y=0;y<lcdRows;++y){
		for(int x=0;x<lcdColumns;++x){
			lcdLines[y][x]=' ';
		}
	}
}
void display_clear_force(){
	for(int y=0;y<lcdRows;++y){
		for(int x=0;x<lcdColumns;++x){
			lcdLines[y][x]=' ';
			lcdLines_prev[y][x]='0';
		}
	}
}

void display(const String& str){
#ifdef DEBUG_SERIAL
	Serial.println(str);
#endif
	display_clear();
	int len=str.length();
	int x=0;
	int y=0;
	for(int i=0;i<len;++i){
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
	__display_prev=-CLOCKS_PER_SEC;
	lcd.init();
	lcd.backlight();
	display_clear_force();
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
	if(__display_prev+CLOCKS_PER_SEC/24>clock_get()){
		return;
	}
	for(int i=0;i<lcdRows;++i){
		if(__diff(lcdLines[i], lcdLines_prev[i], lcdColumns)){
			lcd.setCursor(0, i);
			lcd.printstr(lcdLines[i]);
		}
	}
	__display_prev=clock_get();
}
