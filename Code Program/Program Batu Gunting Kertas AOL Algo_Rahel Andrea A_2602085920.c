#include <stdio.h> // untuk fungsi input output
#include <stdlib.h> // untuk operasi-operasi
#include <string.h> // untuk manipulasi string (strcmp, dll)
#include <windows.h> // untuk fungsi system()

// Menggunakan struct untuk menampung variabel" leaderboard
struct LeaderBoard{
    // string nama sepanjang maksimal 5 karakter, dibuat [6] untuk menampung \0 dan meminimalisir error
    char name[6]; 
    // deklarasi skor menggunakan int (bilangan bulat)
    int score;
};

// fungsi untuk menempatkan kursor ditempat yang kita inginkan (koordinatnya)
void gotoxy(int x, int y){
    HANDLE hConsoleOutput;
    COORD dwCursorPosition;
    dwCursorPosition.X = x;
    dwCursorPosition.Y = y;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

// fungsi untuk membuat tulisan berwarna pada program
void setColor(unsigned short color){
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon, color);
}

// fungsi untuk membuat loading bar / tampilan loading
void loadingBar(){
    system("cls");
    // 0 black background
    // A green foreground
    system("color 0A");

    char a=177, b=219;

    gotoxy(50, 10); printf("Loading...");
    gotoxy(50, 12);
    for(int i=0; i<15; i++){
        printf("%c", a);
    }
    gotoxy(50, 12); 
    for(int i=0; i<15; i++){
        printf("%c", b);
        Sleep(75);
    }
}

// fungsi untuk membuat tampilan loading bertulis "bye bye"
void byeBar(){
    system("cls");
    // 0 black background
    // A green foreground
    system("color 0A");

    char a=177, b=219;

    gotoxy(50, 10); printf("Bye-bye...");
    gotoxy(50, 12);
    for(int i=0; i<15; i++){
        printf("%c", a);
    }
    gotoxy(50, 12); 
    for(int i=0; i<15; i++){
        printf("%c", b);
        Sleep(75);
    }
}

// fungsi untuk mendapatkan pilihan computer menggunakan random (s/c/p)
int compChoice(){
    int n; char computer;
    // mengambil nilai random yang akan dimodulus dengan 100 agar mendapat nilai 0-99
    n = rand()%100;

    // batu / stone : apabila nilai n kurang dari 33
    if(n<33) computer='s';
    // gunting / scissor : apabila nilai n>=33 dan n<66
    else if(n>=33 && n<66) computer='c';
    // kertas / paper : apabila nilai n lebih dari 66
    else computer='p';

    // akan mengembalikan nilai char computer berupa 's'/'c'/'p'
    return computer;
}

// fungsi untuk memasukkan record ke dalam file LeaderBoard.txt
void inputRecord(char nama[6], int score){
    // kita akan buka dan tambahkan isinya menggunakan "a" di LeaderBoard.txt
    FILE *fp;
    fp = fopen("LeaderBoard.txt", "a");
    // kita print datanya menggunakan format "nama;score\n" di dalam filenya
    fprintf(fp, "%.5s;%d\n", nama, score);
    // tutup file
    fclose(fp);
}

// fungsi untuk mengurutkan skor dari yang tertinggi di dalam file
void sort(){
    // menggunakan array of structure untuk menampung nilai-nilai
    struct LeaderBoard lb[1000];
    // digunakan untuk menampung nilai yang digunakan sementara
    struct LeaderBoard temp;
    // membuka file dan membacanya
    FILE *fp;
    fp = fopen("LeaderBoard.txt", "r+");
    int n=0;
    // memasukkan nilai di file ke dalam array of structure lb dengan menghitung jumlahnya melalui variable n
    while(fscanf(fp, "%[^';'];%d\n", lb[n].name, &lb[n].score)!=EOF){
        n++;
    }
    // menggunakan bubble sort, kita akan mengurutkan dari yang tertinggi
    for(int i=0; i<n-1; i++){
        for(int j=i+1; j<n; j++){
            // apabila data di atas lebih kecil dari yang dibawah, maka kedua data tersebut akan ditukar posisinya
            if(lb[i].score<lb[j].score){
                temp=lb[i];
                lb[i]=lb[j];
                lb[j]=temp;
            }
        }
    }
    // berfungsi untuk mengembalikan posisi FILE ke awal
    rewind(fp);
    // kita akan memasukkan nilai yang ada di array of structure lb tadi ke FILE LeaderBoard.txt menggunakan fprintf
    for(int i=0; i<n; i++){
        fprintf(fp, "%s;%d\n", lb[i].name, lb[i].score);
    }
    // menutup file
    fclose(fp);
}

// fungsi untuk menampilkan record yang sudah dalam keadaan urut sesuai score
void displayRecord(){
    // akan membersihkan tampilan layar
    system("cls");
    // menggunakan array of structure lb untuk menampung nilai-nilai di file
    struct LeaderBoard lb[1000];
    // sebelum masuk ke tampilan, kita perlu sort terlebih dahulu isi filenya
    sort();
    // membuka file dalam mode "r" yaitu read atau membaca file saja
    FILE *fp;
    fp = fopen("LeaderBoard.txt", "r");
    int n=0;
    // memasukkan nilai di file ke dalam array of structure lb dengan menghitung jumlahnya melalui variable n
    while(fscanf(fp, "%[^';'];%d\n", lb[n].name, &lb[n].score)!=EOF){
        n++;
    }
    // menggunakan gotoxy agar tampilan berada di tengah
    gotoxy(45, 7); printf("=======================\n");
    gotoxy(45, 8); printf("|Rank|  Name  | Score |\n");
    gotoxy(45, 9); printf("=======================\n");
    int i;
    // akan menampilkan rank, name dan score dari file LeaderBoard.txt
    for(i=0; i<n; i++){
        // untuk ranknya menggunakan (i+1, dimulai dari 1)
        gotoxy(45, 10+i); printf("|%4d|   %5s|%7d|\n", i+1, lb[i].name, lb[i].score);
    }
    gotoxy(45, 10+i); printf("=======================\n");
    gotoxy(45, 12+i); system("pause");
    // menutup file
    fclose(fp);
}

// fungsi untuk menghapus record : diawal akan ditampilkan datanya (secara urut), kemudian user akan diminta menginput nama yang datanya ingin dihapus
// program akan mencocokan dan akan menghapus, lalu data akan ditampilkan kembali
void deleteRecord(){
    // akan membersihkan tampilan layar
    system("cls");
    // menggunakan array of structure lb untuk menampung nilai-nilai di file
    struct LeaderBoard lb[1000];
    // sebelum masuk ke tampilan, kita perlu sort terlebih dahulu isi filenya
    sort();
    // membuka file dalam mode baca "r"/read
    FILE *fp;
    fp = fopen("LeaderBoard.txt", "r");
    int n=0;
    // memasukkan nilai di file ke dalam array of structure lb dengan menghitung jumlahnya melalui variable n
    while(fscanf(fp, "%[^';'];%d\n", lb[n].name, &lb[n].score)!=EOF){
        n++;
    }
    // menggunakan fitur gotoxy agar tampilan bisa di tengah sesuai koordinat yang diberikan
    gotoxy(45, 7); printf("=======================\n");
    gotoxy(45, 8); printf("|Rank|  Name  | Score |\n");
    gotoxy(45, 9); printf("=======================\n");
    int i;
    for(i=0; i<n; i++){
        // akan menampilkan seluruh data di dalam file LeaderBoard.txt
        gotoxy(45, 10+i); printf("|%4d|   %5s|%7d|\n", i+1, lb[i].name, lb[i].score);
    }
    gotoxy(45, 10+i); printf("=======================\n");
    char nama[6]; int tanda=0;
    // kita tutup dahulu filenya, lalu kita buka dalam mode write/"w"
    fclose(fp);
    fp = fopen("LeaderBoard.txt", "w");
    // user akan diminta memasukkan nama yang datanya ingin dihapus
    gotoxy(40, 12+i); printf("Enter the name you want to delete : "); scanf(" %[^\n]", nama); getchar();
    // program akan mencocokan nama yang dimasukkan user dengan nama yang ada di array of structure lb
    for(int j=0; j<n; j++){
        // apabila ada yang cocok, maka program akan berlanjut dengan tidak meng-print data tersebut dan akan memberi nilai tanda=1
        if(strcmp(nama, lb[j].name)==0){
            tanda=1;
            continue;
        // apabila tidak cocok, maka program akan memasukkan nilai-nilai itu ke dalam file lagi
        }else{
            fprintf(fp, "%.5s;%d\n", lb[j].name, lb[j].score);
        }
    }// menutup file karena sudah selesai digunakan
    fclose(fp);
    // apabila tanda==1, maka itu berarti ada data yang cocok dan berhasil dihapus
    if(tanda==1){
        gotoxy(45, 14+i); printf("Deleted.");
        gotoxy(45, 16+i); system("pause"); // system("pause") digunakan menahan layar
        displayRecord(); // akan men-display data
    }// apabila tanda!=1, maka tidak ada kecocokan antara nama yang diinput user dengan yang ada di file, sehingga mengeluarkan "Name not found"
    else{
        gotoxy(45, 14+i); printf("Name not found.");
        gotoxy(45, 16+i); system("pause"); // system("pause") digunakan menahan layar
        displayRecord(); // akan men-display data
    }
    system("cls"); // membersihkan tampilan layar
    char yes;
    // program meminta inputan user apakah ingin menghapus data lagi atau tidak
    gotoxy(45, 10); printf("Delete again (y/n) : "); scanf(" %c", &yes); getchar();
    // apabila user menjawab 'y', maka fungsi akan memanggil diri sendiri (deleteRecord) (Recursive)
    // apabila menjawab selain 'y', maka fungsi ini akan terhenti
    if(yes=='y'){
        deleteRecord();
    }
}

// fungsi untuk mengedit nama di dalam data : diawal akan ditampilkan datanya (secara urut), kemudian user akan diminta menginput nama yang datanya ingin diedit (mengedit namanya saja)
// program akan mencocokkan dan ketika cocok, program akan meminta inputan user mengenai nama yang baru, dan setelah itu nama yang baru akan dimasukkan ke dalam file dan ditampilkan kembali di akhir fungsi
void editRecord(){
    system("cls"); // membersihkan tampilan layar
    struct LeaderBoard lb[1000]; // array of structure lb
    sort(); // mengurutkan data di dalam file terlebih dahulu
    // membuka file dalam mode read / "r"
    FILE *fp;
    fp = fopen("LeaderBoard.txt", "r");
    int n=0;
    // memasukkan nilai di file ke dalam array of structure lb dengan menghitung jumlahnya melalui variable n
    while(fscanf(fp, "%[^';'];%d\n", lb[n].name, &lb[n].score)!=EOF){
        n++;
    }
    // menggunakan fitur gotoxy agar tampilan bisa di tengah sesuai koordinat yang diberikan
    gotoxy(45, 7); printf("=======================\n");
    gotoxy(45, 8); printf("|Rank|  Name  | Score |\n");
    gotoxy(45, 9); printf("=======================\n");
    int i;
    for(i=0; i<n; i++){
        // akan menampilkan seluruh data di dalam file LeaderBoard.txt
        gotoxy(45, 10+i); printf("|%4d|   %5s|%7d|\n", i+1, lb[i].name, lb[i].score);
    }
    gotoxy(45, 10+i); printf("=======================\n");
    char nama[6]; int tanda=0;
    // kita tutup dahulu filenya, lalu kita buka dalam mode write/"w"
    fclose(fp);
    fp = fopen("LeaderBoard.txt", "w");
    gotoxy(40, 12+i); printf("Enter the name you want to edit : "); scanf(" %[^\n]", nama); getchar();
    // program akan mencocokan nama yang dimasukkan user dengan nama yang ada di array of structure lb
    for(int j=0; j<n; j++){
        // apabila ada yang cocok, maka program akan meminta inputan nama yang baru dan akan dimasukkan ke dalam file LeaderBoard.txt
        if(strcmp(nama, lb[j].name)==0){
            tanda=1;
            gotoxy(40, 14+i); printf("Enter the new name : "); scanf(" %[^\n]", lb[j].name); getchar();
            fprintf(fp, "%.5s;%d\n", lb[j].name, lb[j].score);
        // apabila tidak cocok, maka program akan memasukkan nilai-nilai itu ke dalam file lagi
        }else{
            fprintf(fp, "%.5s;%d\n", lb[j].name, lb[j].score);
        }
    }// menutup file karena sudah selesai digunakan
    fclose(fp);
    // apabila tanda==1, maka itu berarti ada data yang cocok dan berhasil diedit
    if(tanda==1){
        gotoxy(45, 16+i); printf("Edited.");
        gotoxy(45, 18+i); system("pause");// system("pause") digunakan menahan layar
        displayRecord(); // akan men-display data
    }// apabila tanda!=1, maka tidak ada kecocokan antara nama yang diinput user dengan yang ada di file, sehingga mengeluarkan "Name not found"
    else{
        gotoxy(45, 14+i); printf("Name not found.");
        gotoxy(45, 16+i); system("pause");// system("pause") digunakan menahan layar
        displayRecord(); // akan men-display data
    }
    system("cls"); // membersihkan tampilan layar
    char yes;
    // program meminta inputan user apakah ingin mengedit data lagi atau tidak
    gotoxy(45, 10); printf("Edit again (y/n) : "); scanf(" %c", &yes); getchar();
    // apabila user menjawab 'y', maka fungsi akan memanggil diri sendiri (editRecord) (Recursive)
    // apabila menjawab selain 'y', maka fungsi ini akan terhenti
    if(yes=='y'){
        editRecord();
    }
}

/* fungsi untuk memainkan gamenya : di awal user akan diberi pilihan ingin main berapa ronde (5/10/15)
 Setelah memilih ingin berapa ronde, user akan memasukkan nama diri dan nama lawan
 Game dimulai, user diminta menginput 's':stone/'c':scissor/'p':paper
 Sesuai dengan aturan batu gunting kertas, user akan bertambah 1 poin apabila berhasil menang, dan sebaliknya
 diakhir ronde akan muncul tulisan besar bertuliskan "YOU WON" apabila skor user lebih tinggi daripada lawan
 "YOU LOSE" apabila skor user lebih rendah dari skor lawan dan "DRAw" apabila skor user dan lawan sama
 data nama dan skor akan dimasukkan dalam file LeaderBoard.txt */
void play(){
    system("cls"); // membersihkan tampilan layar
    int choice;
    // ketika inputan user tidak sesuai, maka program akan mengulang meminta user menginput kembali
    do{
        // menggunakan fitur gotoxy agar tampilan bisa di tengah sesuai koordinat yang diberikan
        gotoxy(50, 10); printf("Choose :\n");
        gotoxy(50, 11); printf("1. 5 rounds\n");
        gotoxy(50, 12); printf("2. 10 rounds\n");
        gotoxy(50, 13); printf("3. 15 rounds\n");
        gotoxy(50, 14); printf("Enter your choice : "); scanf(" %d", &choice);
    }while(choice<1 || choice>3);
    int turn;
    if(choice==1) turn=5; // akan main sebanyak 5 ronde
    else if(choice==2) turn=10; // akan main sebanyak 10 ronde
    else if(choice==3) turn=15; // akan main sebanyak 15 ronde
    char userName[6], compName[6];
    // meminta inputan nama user
    system("cls");
    gotoxy(25, 10); printf("Enter your name (max 5 character) : "); scanf(" %[^\n]", userName); getchar();
    // meminta inputan nama lawan
    system("cls");
    gotoxy(25, 10); printf("Enter your opponent's name (max 5 character) : "); scanf(" %[^\n]", compName); getchar();
    
    int userScore = 0, compScore = 0;

    for(int i=1; i<=turn; i++){
        char userChoice;
        // akan mengeluarkan pilihan untuk dipilih user, apabila user salah menginput, maka akan diminta inputan kembali
        do{
            system("cls");
            gotoxy(50, 6); printf("Round %d :\n", i);
            gotoxy(50, 8); printf("=================");
            gotoxy(50, 9); printf("|Select one :   |\n");
            gotoxy(50, 10); printf("|'s' for stone  |\n");
            gotoxy(50, 11); printf("|'c' for scissor|\n");
            gotoxy(50, 12); printf("|'p' for paper  |\n");
            gotoxy(50, 13); printf("=================");
            gotoxy(50, 15); printf("Your choice : "); scanf(" %c", &userChoice); getchar();
        }while(userChoice != 's' && userChoice != 'c' && userChoice != 'p');
        
        // mengambil nilai char computerChoice / pilihan komputer berdasarkan fungsi random di compChoice()
        char computerChoice = compChoice();
        Sleep(1000); // timer agar tidak langsung keluar yang selanjutnya
        gotoxy(50, 16); printf("%.5s choice : %c\n", compName, computerChoice);
        Sleep(1000);
        // apabila pilihannya sama antara user dengan komputer, maka skor tetap dan akan mengeluarkan "DRAW"
        if(userChoice == computerChoice){
            gotoxy(50, 18); printf("Your score : %d\n", userScore);
			gotoxy(50, 19); printf("%.5s score : %d\n", compName, compScore);
            gotoxy(50, 21); printf("==================\n");
            gotoxy(50, 22); printf("= Round %d : DRAW =\n", i);
            gotoxy(50, 23); printf("==================\n");
            gotoxy(50, 25); system("pause");
        // apabila pilihan user menang dari pilihan komputer, maka skor user akan bertambah dan akan mengeluarkan "YOU WON"
        }else if(userChoice == 's' && computerChoice == 'c' || userChoice == 'c' && computerChoice == 'p' || userChoice == 'p' && computerChoice == 's'){
            userScore++;
            gotoxy(50, 18); printf("Your score : %d\n", userScore);
			gotoxy(50, 19); printf("%.5s score : %d\n", compName, compScore);
			gotoxy(50, 21); printf("=====================\n");
            gotoxy(50, 22); printf("= Round %d : YOU WON =\n", i);
            gotoxy(50, 23); printf("=====================\n");
            gotoxy(50, 25); system("pause");
		}// apabila pilihan komputer menang dari pilihan user, maka skor komputer / lawan akan bertambah dan akan mengeluarkan "YOU LOSE"
        else{
            compScore++;
            gotoxy(50, 18); printf("Your score : %d\n", userScore);
			gotoxy(50, 19); printf("%.5s score : %d\n", compName, compScore);
            gotoxy(50, 21); printf("======================\n");
            gotoxy(50, 22); printf("= Round %d : YOU LOSE =\n", i);
            gotoxy(50, 23); printf("======================\n");
            gotoxy(50, 25); system("pause");
        }
    }
    // apabila hasil akhir skor user lebih tinggi, maka akan mengeluarkan tulisan besar "YOU WON"
    if(userScore>compScore){
    	system("cls");
        gotoxy(40, 10); printf(" __   __  _______  __   __    _     _  _______  __    _ ");
        gotoxy(40, 11); printf("|  | |  ||       ||  | |  |  | | _ | ||       ||  |  | |");
        gotoxy(40, 12); printf("|  |_|  ||   _   ||  | |  |  | || || ||   _   ||   |_| |");
        gotoxy(40, 13); printf("|       ||  | |  ||  |_|  |  |       ||  | |  ||       |");
        gotoxy(40, 14); printf("|_     _||  |_|  ||       |  |       ||  |_|  ||  _    |");
        gotoxy(40, 15); printf("  |   |  |       ||       |  |   _   ||       || | |   |");
        gotoxy(40, 16); printf("  |___|  |_______||_______|  |__| |__||_______||_|  |__|\n\n");
        gotoxy(40, 18); system("pause");
    }// apabila hasil akhir skor komputer / lawan lebih tinggi, maka akan mengeluarkan tulisan besar "YOU LOSE"
    else if(compScore>userScore){
        system("cls");
        gotoxy(40, 10); printf(" __   __  _______  __   __    ___      _______  _______  _______ ");
        gotoxy(40, 11); printf("|  | |  ||       ||  | |  |  |   |    |       ||       ||       |");
        gotoxy(40, 12); printf("|  |_|  ||   _   ||  | |  |  |   |    |   _   ||  _____||    ___|");
        gotoxy(40, 13); printf("|       ||  | |  ||  |_|  |  |   |    |  | |  || |_____ |   |___ ");
        gotoxy(40, 14); printf("|_     _||  |_|  ||       |  |   |___ |  |_|  ||_____  ||    ___|");
        gotoxy(40, 15); printf("  |   |  |       ||       |  |       ||       | _____| ||   |___ ");
        gotoxy(40, 16); printf("  |___|  |_______||_______|  |_______||_______||_______||_______|\n\n");
        gotoxy(40, 18); system("pause");
    }// apabila skor user dan skor komputer / lawan sama, maka akan mengeluarkan tulisan besar "DRAW"
    else{
        system("cls");
        gotoxy(40, 10); printf(" ______   ______    _______  _     _ ");
        gotoxy(40, 11); printf("|      | |    _ |  |   _   || | _ | |");
        gotoxy(40, 12); printf("|  _    ||   | ||  |  |_|  || || || |");
        gotoxy(40, 13); printf("| | |   ||   |_||_ |       ||       |");
        gotoxy(40, 14); printf("| |_|   ||    __  ||       ||       |");
        gotoxy(40, 15); printf("|       ||   |  | ||   _   ||   _   |");
        gotoxy(40, 16); printf("|______| |___|  |_||__| |__||__| |__|");
        gotoxy(40, 18); system("pause");
    }
    // setelah mendapat data nama dan skor user, serta data nama dan skor komputer / lawan
    // kita akan masukkan data ini ke dalam file menggunakan fungsi inputRecord dengan menggunakan 2 parameter pass by reference (nama dan skor)
    inputRecord(userName, userScore);
    inputRecord(compName, compScore);
}

// driver code
int main(){
    // program akan mengulang terus menerus
    while(1){
        setColor(10); // merubah teks agar menjadi warna hijau
        int choice;
        // menu yang ditampilkan untuk dipilih
        do{
        	system("cls");
			gotoxy(50, 10); printf("GAME ROCK PAPER SCISSOR\n");
	        gotoxy(50, 12); printf("1. Play\n");
	        gotoxy(50, 13); printf("2. Display LeaderBoard\n");
	        gotoxy(50, 14); printf("3. Delete\n");
	        gotoxy(50, 15); printf("4. Edit Name\n");
	        gotoxy(50, 16); printf("5. Exit Game\n");
            gotoxy(50, 18); printf("Enter your choice : "); scanf(" %d", &choice); getchar();
        }while(choice<1 || choice>5); 

        // berdasarkan yang user pilih, akan menuju ke fungsi yang berkaitan
        switch(choice){
            case 1:
                loadingBar();
                play();
                break;

            case 2:
                loadingBar();
                displayRecord();
                break;

            case 3:
                loadingBar();
                deleteRecord();
                break;

            case 4:
                loadingBar();
                editRecord();
                break;

            case 5:
                // keluar dari program, terhenti dari while
                byeBar();
                exit(0);
                break;
                
            default:
                printf("\nInvalid Choice\n");
                system("pause");
        }
    }
}

