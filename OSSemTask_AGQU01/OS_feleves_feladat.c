#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>

#define SHMKEY 69905L

int main()
{
	int shmid;
	key_t key;
	int size=512;
	int shmflg;
	int rtn;
	struct vmi {
		int  hossz;
		char szoveg[512-sizeof(int)];
	} *segm;

	key = SHMKEY;

    printf("Milyen muveletet szeretne vegezni az osztott memorian?\n");
    printf("0-letrehozas\n");
    printf("1-olvasas\n");
    printf("2-iras\n");
    printf("3-torles\n");
    int muvelet;
    scanf("%d",&muvelet);

    shmflg = 0;

    switch(muvelet){

    case 0 :

	if ((shmid=shmget(key, size, shmflg)) < 0) {
	   printf("Nincs meg szegmens! Keszitsuk el!\n");
	   shmflg = 00666 | IPC_CREAT;
	   if ((shmid=shmget(key, size, shmflg)) < 0) {
	      perror("Az shmget() system-call sikertelen!\n");
	      exit(-1);
	   }
	} else printf("Van mar ilyen shm szegmens!\n");

	printf("\nAz shm szegmens azonositoja %d: \n", shmid);

	exit(0);
	break;

	case 1:
	if ((shmid=shmget(key, size, shmflg)) < 0) {
	   printf("Nincs meg szegmens! Keszitsuk el!\n");
	   shmflg = 00666 | IPC_CREAT;
	   if ((shmid=shmget(key, size, shmflg)) < 0) {
	      perror("Az shmget() system-call sikertelen!\n");
	      exit(-1);
	   }
	}


	shmflg = 00666 | SHM_RND;
	segm = (struct vmi *)shmat(shmid, NULL, shmflg);

	if (segm == (void *)-1) {
		perror("Sikertelen attach!\n");
		exit(-1);
		}

	if (strlen(segm->szoveg) > 0) {
		printf("\nA kiolvasott szoveg: %s",segm->szoveg);}
	break;
	case 2:
	if ((shmid=shmget(key, size, shmflg)) < 0) {
	   shmflg = 00666 | IPC_CREAT;
	   if ((shmid=shmget(key, size, shmflg)) < 0) {
	      perror("Az shmget() system-call sikertelen!\n");
	      exit(-1);
	   }
	}
	shmflg = 00666 | SHM_RND;
	segm = (struct vmi *)shmat(shmid, NULL, shmflg);
	if (segm == (void *)-1) {
		perror("Sikertelen attach!\n");
		exit(-1);
	}
	printf("\nUj szoveget kerek!\n");
        scanf("%s",segm->szoveg);
        printf("Az uj szoveg: %s\n",segm->szoveg);
	segm->hossz=strlen(segm->szoveg);
	break;

	case 3:
	if ((shmid=shmget(key, size, shmflg)) < 0) {
	   shmflg = 00666 | IPC_CREAT;
	   if ((shmid=shmget(key, size, shmflg)) < 0) {
	      perror("Az shmget() system-call sikertelen!\n");
	      exit(-1);
	   }
	}

	rtn = shmctl(shmid, IPC_RMID, NULL);
    printf("Szegmens torolve. Hibakod: %d\n", rtn);
    break;
}}
