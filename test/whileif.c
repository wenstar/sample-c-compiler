int a,b,i;
a = 0;
b = 10;
i = 0;
while(a < 20){
    if(a < b){
        while(i < 5){
            print('+');
            i = i + 1;
        }
    }
    a = a + 1;
    while(i<10){
        print('-');
        i = i+1;
    }
    print('!');
}
