#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

FILE *dosya; 

struct Personel {
    char TCKimlik[12];
    char Isim[50];
    char Soyisim[50];
    char Telefon[12];
    char CalistigiBolum[50];
};

void kayitListele() {
   
    dosya = fopen("personel.txt", "r");   // okuma modunda dosyayý açýyoruz

    if (dosya == NULL) { 
        printf("Dosya acilamadi.\n");
        
    }

    int c;
	if (dosya) 
	{
		while ((c = getc(dosya)) != EOF)
			putchar(c);
		fclose(dosya);
	}	

    
}

int tcVarMi(const char *tcKimlik) {
    dosya = fopen("personel.txt", "r");
    char tc[11 + 1];
    while (fscanf(dosya, "%s", tc) != EOF) {
        if (strcmp(tc, tcKimlik) == 0) {
            fclose(dosya);
            return 1; // TC kimlik numarasý bulundu
        }
    }
    
    return 0; // TC kimlik numarasý bulunamadý
}

void kayitAra(char aranan[]) {

    
    
    char isim[15 + 1];
    char soyisim[15 + 1];
    char tcKimlik[11 + 1];
    char calistigiBolum[30 + 1];
    char telNo[11 + 1];

    int kayitYok = 1; // Varsayýlan olarak kayýt yok olarak ayarlanýr.

    dosya = fopen("personel.txt", "r");

    if (dosya == NULL) {
        printf("Dosya acilamadi.\n");
        return;
    }

    printf("Aranacak kriter: %s\n", aranan);

    while (fscanf(dosya, "%s %s %s %s %s", tcKimlik, isim, soyisim, telNo, calistigiBolum) != EOF) {
        if (strstr(tcKimlik, aranan) != NULL || strstr(isim, aranan) != NULL ||
            strstr(soyisim, aranan) != NULL || strstr(telNo, aranan) != NULL ||
            strstr(calistigiBolum, aranan) != NULL) {
            printf("| %s | %s | %s | %s | %s |\n", tcKimlik, isim, soyisim, telNo, calistigiBolum);
            kayitYok = 0; // Eðer bir eþleþme bulunursa kayýt yok flag'ini güncelle.
        }
    }

    if (kayitYok)
        printf("Aranilan Kayit Bulunamadi : %s\n", aranan);

    fclose(dosya);
    
    
    
    
    
    
}

void kayitSil(const char *tcSil) {
    FILE *dosya, *geciciDosya;

 
    char tcKimlik[12];
    char isim[16];
    char soyisim[16];
    char telNo[12];
    char calistigiBolum[31];

    dosya = fopen("personel.txt", "r");
    geciciDosya = fopen("gecici.txt", "w");

    if (dosya == NULL || geciciDosya == NULL) {
        printf("Dosya acilamadi.\n");
        return;
    }

    int kayitBulundu = 0;

    while (fscanf(dosya, "%s %s %s %s %s", tcKimlik, isim, soyisim, telNo, calistigiBolum) != EOF) {
        if (strcmp(tcSil, tcKimlik) == 0) {
            printf("Silinen Kayit: %s %s %s %s %s\n", tcKimlik, isim, soyisim, telNo, calistigiBolum);
            kayitBulundu = 1;
        } else {
            fprintf(geciciDosya, "%s %s %s %s %s\n", tcKimlik, isim, soyisim, telNo, calistigiBolum);
        }
    }

    if (!kayitBulundu) {
        printf("Aranilan Kayit Bulunamadi : %s\n", tcSil);
    }

    fclose(dosya);
    fclose(geciciDosya);

    // Dosyayý sil ve geçici dosyayý eski dosyanýn adýyla yeniden adlandýr
    remove("personel.txt");
    rename("gecici.txt", "personel.txt");
}

void personelGuncelle(const char *tcGuncelle) {
    
   
    FILE *dosya, *geciciDosya;
    struct Personel personel;
 



    dosya = fopen("personel.txt", "r");
    geciciDosya = fopen("gecici.txt", "w");

    if (dosya == NULL || geciciDosya == NULL) {
        printf("Dosya acilamadi.\n");
        return;
    }

    int kayitBulundu = 0;

    while (fscanf(dosya, "%s %s %s %s %s", personel.TCKimlik, personel.Isim, personel.Soyisim,
                  personel.Telefon, personel.CalistigiBolum) != EOF) {
        if (strcmp(tcGuncelle, personel.TCKimlik) == 0) {
            printf("Mevcut Bilgiler:\n");
            printf("Isim: %s\n", personel.Isim);
            printf("Soyisim: %s\n", personel.Soyisim);
            printf("Telefon: %s\n", personel.Telefon);
            printf("Calistigi Bolum: %s\n", personel.CalistigiBolum);

            printf("\nYeni Bilgileri Girin:\n");
            printf("Isim: ");
            scanf("%s", personel.Isim);
            printf("Soyisim: ");
            scanf("%s", personel.Soyisim);
            printf("Telefon: ");
            scanf("%s", personel.Telefon);
            printf("Calistigi Bolum: ");
            scanf("%s", personel.CalistigiBolum);

            kayitBulundu = 1;
        }
        fprintf(geciciDosya, "%s %s %s %s %s\n", personel.TCKimlik, personel.Isim, personel.Soyisim,
                personel.Telefon, personel.CalistigiBolum);
    }

    if (!kayitBulundu) {
        printf("Aranilan Kayit Bulunamadi : %s\n", tcGuncelle);
    }

    fclose(dosya);
    fclose(geciciDosya);

    remove("personel.txt");
    rename("gecici.txt", "personel.txt");
}

void kayitEkle() {
      char isim[15 + 1];
    char soyisim[15 + 1];
    char tcKimlik[11 + 1];
    char calistigiBolum[30 + 1];
    char telNo[11 + 1];

    dosya = fopen("personel.txt", "a");

    if (dosya == NULL) {
        printf("Dosya acilamadi.\n");
        return;
    }


	
	
	while(1){
			
    dosya = fopen("personel.txt", "a");
			printf("\n Kisi tc kimlik no : ");
    scanf("%s", tcKimlik);
		
		
		
		if(tcVarMi(tcKimlik) == 0){
			 dosya = fopen("personel.txt", "a");
			break;
			}else 
		{
			printf("\n bu tc kimlik no sahip kayit zaten var tekrar giriniz\n");
		 dosya = fopen("personel.txt", "a");
			continue;
		}

	}
	
	 dosya = fopen("personel.txt", "a");
	
    
    

    printf("\n Kisi adi: ");
    scanf("%s", isim);

    printf("\n Kisi soyadi: ");
    scanf("%s", soyisim);

    printf("\n Kisi telefon numarasi: ");
    scanf("%s", telNo);

    printf("\n Calistigi bolum  :");
    scanf("%s", calistigiBolum);

    // Her bir alanýn arasýna 1 boþluk ekleyerek dosyaya yaz
    fprintf(dosya, "\n%s %s %s %s %s", tcKimlik, isim, soyisim, telNo, calistigiBolum);

    fclose(dosya);
}

int main(){
	int secim;
	char devam;


	do {
		
		 printf("\n------ PERSONEL KAYIT PROGRAMI ------\n");
        // Menüyü ekrana yazdýr
        printf("\n--- MENU ---\n");
        printf("1. Kayit Listele\n");
        printf("2. Kayit Ara\n");
        printf("3. Kayit Ekle\n");
        printf("4. Kayit Sil\n");
        printf("5. Kayit Guncelle\n");
        printf("6. Programdan Cikis\n");
        printf("Seciminizi yapin (1-6): ");
        scanf("%d", &secim);

        switch (secim) {
            case 1:
            	kayitListele();
                break;
            
			case 2:
		
		 char arananSoyisim[32];
         int aramaSecim;
		 printf("Kaydini Aramak istediginiz personelin herhangi bir kriterini giriniz (tc ,tel no , isim ,soyisim , calýstigi bolum) ");
	     scanf("%s", arananSoyisim);
         kayitAra(arananSoyisim);
              break;
          
		    case 3:
               kayitEkle();
               break;
            
			case 4:
             char tcSil[12];
              printf("Silinecek personelin TC Kimlik numarasini girin: ");
              scanf("%s", tcSil);
               kayitSil(tcSil);
			   
			     break;
         
		    case 5:
         
               char tcGuncelle[12];
               printf("Guncellenecek personelin TC Kimlik numarasini girin: ");
             scanf("%s", tcGuncelle);

               personelGuncelle(tcGuncelle);
              
               
               
                break;
            case 6:
              
                break;
            default:
                printf("Gecersiz secim. Lutfen tekrar deneyin.\n");
        }
    } while (secim != 6);

return 0;	
}













	
	
	
	









