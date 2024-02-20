#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>


#define PASSANGER_FILE "passanger.txt"
#define FLIGHT_FILE "flight.txt"
#define MAX_NAME 100
#define CODE_MAX 100
#define AIRLINE_MAX 100

typedef struct{ //struct untuk menyimpan tanggal penerbangan
	int yyyy;
	int mm;
	int dd;
}date;

typedef struct{ //struct untuk menyimpan data penumpang
	date flightDate;
	char passangerName[MAX_NAME];
	char airline[AIRLINE_MAX];
	int flightCode[CODE_MAX];
}passangerData;

void fgetsRemove(char * restrict buf, int n,FILE * restrict stream){ //menghapus newline pada fgets
    if(fgets(buf, n, stream) == NULL){
        printf("Fail to read the input stream");
    }
    else{
        buf[strcspn(buf, "\n")] = '\0'; //mendapatkan panjang string sebelum newline dan mengganti newline menjadi \0
    }
}

int kabisat(int tahun){ //cek jika kabisat
    return (((tahun % 4 == 0) &&
             (tahun % 100 != 0)) ||
            (tahun % 400 == 0));
}

// cek jika tanggal valid, return 1
int cekTanggal(date *validDate){
    //cek rentang hari, bulan, tahun
    if (validDate->yyyy > 9999 ||validDate->yyyy < 1900)
        return 0;
    if (validDate->mm < 1 || validDate->mm > 12)
        return 0;
    if (validDate->dd < 1 || validDate->dd > 31)
        return 0;
    //untuk bulan februari di tahun kabisat
    if (validDate->mm == 2){
        if (kabisat(validDate->yyyy))
            return (validDate->dd <= 29);
        else
            return (validDate->dd <= 28);
    }
    //untuk bulan dengan 30 hari
    if (validDate->mm == 4 || validDate->mm == 6 || validDate->mm == 9 || validDate->mm == 11)
        return (validDate->dd <= 30);
    return 1;
}

//cek jika nama valid, return 1
int cekNama(const char *name){
    int validName = 1;
    int len = 0;
    len = strlen(name);
    for(int i = 0; i < len ; ++i){
    	//function isalpha untuk cek sebuah karakter adalah alfabet atau bukan
        if(!(isalpha(name[i])) && (name[i] != '\n') && (name[i] != ' ')){
            validName = 0;
            break;
        }
    }
    return validName;
}

void welcomeMessage(){
    printf("\n\n\n\n\n");
    printf("\n\t\t\t        =============================================");
    printf("\n\t\t\t        =                                           =");
    printf("\n\t\t\t        =                 WELCOME TO                =");
    printf("\n\t\t\t        =             Airline Ticketing             =");
    printf("\n\t\t\t        =                                           =");
    printf("\n\t\t\t        =                                           =");
    printf("\n\t\t\t        =============================================");
    printf("\n\n\n\t\t\t Tekan tombol enter untuk lanjut.....");
    getch();
}

void header(){ // header
	system("cls");
    printf("\t\t\t===========================================================================");
	printf("\n\t\t\t=x=x=x=x=x=x                                                   x=x=x=x=x=x=");
    printf("\n\t\t\t=x=x=x=x=x=x                 Airline Ticketing                 x=x=x=x=x=x=");
    printf("\n\t\t\t=x=x=x=x=x=x                                                   x=x=x=x=x=x=");
    printf("\n\t\t\t===========================================================================");
}

void entryPassanger(){
	system("cls");
    passangerData dataBase[100];
    FILE *fp = NULL;
    fp = fopen(PASSANGER_FILE,"r"); // untuk membukan file
    if(fp == NULL){
        printf("\n\t\t\tData tidak tersedia\n"); // jika file tidak dapat ditemukan
        exit(1);
    }
    header(); // memanggil header
    printf("\n\t\t\t============                 Passanger data                    ============");
    printf("\n\t\t\t===========================================================================");
    int counter = 1;
	int i = 0;
	while(!feof(fp)){ // membaca data
		fscanf(fp, "%d/%d/%d\t%s\t%s\t%d\n", &dataBase[i].flightDate.dd, &dataBase[i].flightDate.mm, &dataBase[i].flightDate.yyyy, &dataBase[i].passangerName, &dataBase[i].airline, &dataBase[i].flightCode);
		i++;
	}
	printf("\n\n\n ---------------------------------------------------------------------");
	printf("\n|  Flight Date   |     Passanger    |     Airline     |      Code     |" ); // menampilkan data penumpang
	printf("\n ----------------------------------------------------------------------");
	for(int k=0; k<i; k++){
		printf("\n|   %2d/%2d/%d   |  ", dataBase[k].flightDate.dd, dataBase[k].flightDate.mm, dataBase[k].flightDate.yyyy);
		printf("%12s    |  ", dataBase[k].passangerName);
		printf("%10s   |    ", dataBase[k].airline);
		printf("%10d    |  ", dataBase[k].flightCode);
	}
	printf("\n ---------------------------------------------------------------------------------------------------------------");
	fclose(fp); // menutup file
	printf("\n\n\n\t\t\t Enter untuk kembali ke menu.....");
	getch();
}

void editPassanger(){ // menu untuk mengedit data
    system("cls");
    passangerData passangerData[100];
    header(); //memanggil header
    printf("\n\t\t\t============                    Edit data                      ============");
    printf("\n\t\t\t===========================================================================");
	FILE *fptr;
    int userInput, dd, mm, yy, total;
	char passangerName[MAX_NAME];
	int flightCode[CODE_MAX];
	char airline[AIRLINE_MAX];
    int i = 0, status = 0;
    fptr = fopen(PASSANGER_FILE, "r"); //membuka file
    if(fptr == NULL){
        printf("\n\t\t\tData tidak tersedia\n"); // jika tidak bisa menemukan file
        exit(1);
    }
    while(!feof(fptr)){
		fscanf(fptr, "%d/%d/%d\t%s\t%s\t%d\n", &passangerData[i].flightDate.dd, &passangerData[i].flightDate.mm, &passangerData[i].flightDate.yyyy, &passangerData[i].passangerName, &passangerData[i].airline, &passangerData[i].flightCode);
		i++; //membaca file
	}
	printf("\n\n\t\t\t=x=x=x=x=x=x                       List                        x=x=x=x=x=x=");
	for(int k=0; k<i; k++){
		printf("\n\n\t\t\t---------------------------------------------------------------------------"); // menampilkan data dengan nomor didepannya
		printf("\n\t\t\tNomor\t\t= %d", k+1);
		printf("\n\t\t\tTanggal Event\t= %2d/%2d/%d", passangerData[k].flightDate.dd, passangerData[k].flightDate.mm, passangerData[k].flightDate.yyyy);
		printf("\n\t\t\tNama Event\t= %s", passangerData[k].passangerName);
		printf("\n\t\t\t---------------------------------------------------------------------------");
	}
	fclose(fptr);
    do{
    	status = 1;
		printf("\n\n\t\t\tMasukkan nomor data yang ingin diubah = ");
    	scanf("%d", &userInput);
    	getchar();
    	if(userInput > i || userInput < 1){
    		printf("\n\n\t\t\tTolong masukkan data yang tersedia");
    		status = 0;
		}
	}while(!status);
    userInput-=1;
	fptr = fopen(PASSANGER_FILE, "w");
    for (int k = 0; k<i; k++){
	    if(k == userInput){
			do{
				printf("\n\t\t\tMasukkan tanggal yang baru (dd/mm/yyyy)= "); // memasukkan tanggal baru 
		        scanf("%d/%d/%d", &passangerData[k].flightDate.dd, &passangerData[k].flightDate.mm, &passangerData[k].flightDate.yyyy);
		        status = cekTanggal(&passangerData[k].flightDate);
		        if(!status){
		            printf("\n\t\t\tTanggal yang dimasukkan salah. Tolong ulangi.\n");
		        }
		    }while(!status);
		    do{
		        printf("\n\t\t\tMasukkan nama yang baru = "); // memasukkan nama baru
		        fflush(stdin);
		        fgetsRemove(passangerData[k].passangerName,MAX_NAME,stdin);
		        status = cekNama(passangerData[k].passangerName);
		        if (!status)
		        {
		            printf("\n\t\t\tNama tidak valid. Tolong ulangi.\n");
		        }
		    }while(!status);
		    do{
		        printf("\n\t\t\tMasukkan airline yang baru = "); // memasukkan airline baru
		        fflush(stdin);
		        fgetsRemove(passangerData[k].airline,AIRLINE_MAX,stdin);
		        status = cekNama(passangerData[k].airline);
		        if (!status)
		        {
		            printf("\n\t\t\tNama tidak valid. Tolong ulangi.\n");
		        }
		    }while(!status);
		}
		fprintf(fptr, "%d/%d/%d\t%s\t%s\t%d\n", passangerData[k].flightDate.dd, passangerData[k].flightDate.mm, passangerData[k].flightDate.yyyy, passangerData[k].passangerName, passangerData[k].airline, passangerData[k].flightCode);
    }
    fclose(fptr);
    printf("\n\n\t\t\tData berhasil diupdate");
	printf("\n\n\n\t\t\t Enter untuk kembali ke menu.....");
	getchar();
}

void erase(){ //menu untuk menghapus salah satu data
	system("cls");
    passangerData passangerData[100];
    header(); //memanggil header
    printf("\n\t\t\t============                   Erase data                      ============");
    printf("\n\t\t\t===========================================================================");
	FILE *fp;
    int i = 0, status = 0, userInput;
    fp = fopen(PASSANGER_FILE, "r"); //membuka file
    if(fp == NULL){
        printf("\n\t\t\tData tidak tersedia\n"); // jika file tidak ada
        exit(1);
    }
	while(!feof(fp)){ // membaca file
		fscanf(fp, "%d/%d/%d\t%s\t%s\t%d\n", &passangerData[i].flightDate.dd, &passangerData[i].flightDate.mm, &passangerData[i].flightDate.yyyy, &passangerData[i].passangerName, &passangerData[i].airline, &passangerData[i].flightCode);
		i++;
	}
	printf("\n\n\t\t\t=x=x=x=x=x=x                       List                        x=x=x=x=x=x=");
	for(int k=0; k<i; k++){
		printf("\n\n\t\t\t---------------------------------------------------------------------------"); //menampilkan seluruh data penumpang
		printf("\n\t\t\tNomor\t\t= %d", k+1);
		printf("\n\t\t\tTanggal Event\t= %2d/%2d/%d", passangerData[k].flightDate.dd, passangerData[k].flightDate.mm, passangerData[k].flightDate.yyyy);
		printf("\n\t\t\tNama Event\t= %s", passangerData[k].passangerName);
		printf("\n\t\t\t---------------------------------------------------------------------------");
	}
	fclose(fp);
    do{
    	status = 1;
		printf("\n\n\t\t\tMasukkan nomor data yang ingin dihapus = "); //memilih data mana yang ingin dihapus
    	scanf("%d", &userInput);
    	getchar();
    	if(userInput > i || userInput < 1){
    		printf("\n\n\t\t\tTolong masukkan data yang tersedia");
    		status = 0;
		}
	}while(!status);
    userInput-=1;
	fp = fopen(PASSANGER_FILE, "w"); //membuka file
    for (int k = 0; k<i; k++){
	    if(k == userInput){
			continue; // meloncati data yang dipilih agar tidak tercetak
		}
		fprintf(fp, "%d/%d/%d\t%s\t%s\t%d\n", &passangerData[k].flightDate.dd, &passangerData[k].flightDate.mm, &passangerData[k].flightDate.yyyy, &passangerData[k].passangerName, &passangerData[k].airline, &passangerData[k].flightCode);
    }
    fclose(fp); // menutup file
    printf("\n\n\t\t\tData berhasil dihapus!");
	printf("\n\n\n\t\t\t Enter untuk kembali ke menu.....");
	getchar();
}

void orderTicket(){ // menu pemesanan tiket untuk menambah data pada passanger.txt
	system("cls");
    passangerData passangerData = {0};
    FILE *fp = NULL;
    int status = 0;
    fp = fopen(PASSANGER_FILE,"a+"); //membuka file
    if(fp == NULL){
        printf("\n\t\t\tData tidak tersedia\n"); // jika file tidak ditemukan
        exit(1);
    }
    header(); //memanggil header
    printf("\n\t\t\t===========================================================================");
    printf("\n\t\t\t===========================================================================");
	do{
        //input tanggal
		printf("\n\t\t\tMasukkan tanggal keberangkatan (dd/mm/yyyy)= ");
        scanf("%d/%d/%d", &passangerData.flightDate.dd, &passangerData.flightDate.mm, &passangerData.flightDate.yyyy);
        //cek tanggal valid atau tidak
        status = cekTanggal(&passangerData.flightDate);
        if(!status){ //jika tanggal tidak valid
            printf("\n\t\t\tTanggal yang dimasukkan salah. Tolong ulangi.\n");
        }
    }while(!status);
    do{
        printf("\n\t\t\tPassanger = "); //input nama penumpang
        fflush(stdin);
        fgetsRemove(passangerData.passangerName,MAX_NAME,stdin);
    }while(!status);
    do{
        printf("\n\t\t\tAirline = "); // input nama pesawat yang ingin dipesan
        fflush(stdin);
        fgetsRemove(passangerData.airline,AIRLINE_MAX,stdin);
    }while(!status);


	fprintf(fp, "%d/%d/%d\t%s\t%s\t%d\n", passangerData.flightDate.dd, passangerData.flightDate.mm, passangerData.flightDate.yyyy, passangerData.passangerName, passangerData.airline, passangerData.flightCode);
	fclose(fp); //menutup file
	printf("\n\n\t\tData berhasil ditambahkan!");
	printf("\n\n\n\t\t\t Enter untuk kembali ke menu.....");
	getchar();
}

void menuAdmin(){ // menu khusus admin
	int choice = 0;
	do{
        header();
        printf("\n\t\t\t============                   Welcome admin                   ============");
    	printf("\n\t\t\t===========================================================================");
        printf("\n\n\n\t\t\t1. Passangers info");
        printf("\n\t\t\t2. Edit");
        printf("\n\t\t\t3. Erase");
        printf("\n\n\t\t\t9. Kembali");
        printf("\n\t\t\t0. Exit");
        printf("\n\n\n\t\t\tPilihan anda -> ");
        scanf("%d",&choice);
        switch(choice){
        case 1:
            entryPassanger(); //function untuk memanggil entryPassanger
            break;
        case 2:
        	editPassanger(); //function untuk memanggil editPassanger
        	break;
        case 3:
            erase(); //function untuk memanggil erase
            break;
        case 9:
            portal(); // function untuk kembali ke portal
            break;
        case 0: // untuk menutup program
            printf("\n\n\n\t\t\t\tTerima kasih!\n\n\n\n\n");
            exit(1);
            break;
        default:
            printf("\n\n\n\t\t\tMaaf, pilihan anda salah"); // jika pilihan tidak tersedia
        }
    }
    while(choice!=0);  
}

void login(){ // fungsi login untuk admin
	header();
	const char defaultUsername[] = "harapeco";
	const char defaultPassword[] = "harapeco";
	char username[20];
    char password[20];
    int tryL = 0;
    do{
    	getchar();
        printf("\n\n\n\t\t\t\tUsername: ");
        fgetsRemove(username, sizeof(username),stdin);
        printf("\n\t\t\t\tPassword: ");
        fgetsRemove(password, sizeof(password),stdin);
		if((!strcmp(username, defaultUsername)) && (!strcmp(password, defaultPassword))){
            menuAdmin(); //jika benar akan menuju menu admin
        }
        else{
            printf("\t\t\t\tMaaf, informasi yang Anda masukkan salah");
            tryL++;
        }
    }
    while(tryL<=3);
    if(tryL>3){	//jika percobaan gagal lebih dari 3 kali
        header();
        printf("\n\t\t\t\tLogin Gagal");
        printf("\n\t\t\t\tMaaf, Anda belum terdaftar.");
        getchar();
        exit(1);
    }
}

void menuUser(){ // menu untuk user
	int choice = 0;
	do{
        header();
        printf("\n\t\t\t============                    Welcome user                   ============");
    	printf("\n\t\t\t===========================================================================");
        printf("\n\n\n\t\t\t1. Order ticket");
        printf("\n\n\t\t\t9. Kembali");
        printf("\n\t\t\t0. Exit");
        printf("\n\n\n\t\t\tPilihan anda -> ");
        scanf("%d",&choice);
        switch(choice){
        case 1:
            orderTicket(); //function untuk memanggil fungsi orderTicket
            break;
        case 9:
            portal(); // untuk kembali ke portal
            break;
        case 0:
            printf("\n\n\n\t\t\t\tTerima kasih!\n\n\n\n\n");
            exit(1);
            break;
        default:
            printf("\n\n\n\t\t\tMaaf, pilihan anda salah"); //jika pilihan tidak tersedia
        }
    }
    while(choice!=0);  
}

void portal(){ // portal menu
	header();
	int tempr = 0;
	printf("\n\n\n\t\t\t\t1. Admin");
	printf("\n\t\t\t\t2. User");
	printf("\n\t\t\t\tLogin sebagai: ");
	scanf("%d", &tempr);
	switch(tempr){
		case 1:
			login(); //jika ingin login sebagai admin
			break;
		case 2:
			menuUser(); // jika ingin login sebagai user
			break;
		case 0:
			exit(1); // menutup program
			break;
		default:
			printf("\n\n\n\t\t\tInvalid");
	}
	
}



int checkFile(const char *path){ // cek file sudah ada atau belum
	FILE *fp = fopen(path, "r");
    int status = 0; // default jika file tidak ada, return 0
    if (fp != NULL){
        status = 1; // jika file ada, return 1
        fclose(fp);
    }
    return status;
}

void createFile(){ //buat file jika file belum ada
	FILE *fp = NULL;
    int status = 0;
    status = checkFile(PASSANGER_FILE);
    if(!status) {
        //membuat file
		fp = fopen(PASSANGER_FILE,"w");
		if(fp == NULL){
        	printf("Error dalam pembuatan file.\n");
        	exit(1);
    	}
	}
}

int main(){ // modul utama untuk memanggil semua fungsi
    createFile();
    welcomeMessage();
    portal();
    return 0;
}
