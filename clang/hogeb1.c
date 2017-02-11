#include <stdio.h>
#include <stdbool.h>
#include <time.h>     // for clock()

#define G (6)

#define O ((unsigned long long)1)
#define T ((unsigned long long)2)
#define Y (O<<G)
#define Z (1<<G)
#define F (G*G-1)
#define EE ((O << (G*G-1) ))

int count=0;
void mover(int cur,unsigned long long cpx,unsigned long long cpy);
void moved(int cur,unsigned long long cpx,unsigned long long cpy);
void moveu(int cur,unsigned long long cpx,unsigned long long cpy);
void movel(int cur,unsigned long long cpx,unsigned long long cpy);
void mover(int cur,unsigned long long cpx,unsigned long long cpy){
    if(F==cur+1){
        count++;
        return;
    }

    int c=((cpx>>(cur-1))&6)|((cpy>>cur)&(Z|1))|4;
    int t=cur;
    do{
        if     (c==(Z|3)){cpx|=(T<<cur);cur=cur+1;}
        else if(c==(  7)){cpy|=(Y<<cur);cur=cur+G;}
        else if(c==(Z|5)){cpx|=(O<<cur);cur=cur-1;}
        else if(c==(Z|6)){cpy|=(O<<cur);cur=cur-G;}
        else {break;}
        if(cur==F){
           if(cpx & cpy & EE ){return;}
           break;
        }
        c=((cpx>>(cur-1))&6)|((cpy>>cur)&(Z|1));
    }while(1);

    cpx|=(T<<t);
    cur=t+1;
    if(!((cpx>>cur)&2)){mover(cur,cpx,cpy);}
    if(!((cpy>>cur)&Z)){moved(cur,cpx,cpy);}
    if(!((cpx>>cur)&1)){movel(cur,cpx,cpy);}
    if(!((cpy>>cur)&1)){moveu(cur,cpx,cpy);}
}
void movel(int cur,unsigned long long cpx,unsigned long long cpy){
    if(F==cur-1){
        count++;
        return;
    }

    int c=((cpx>>(cur-1))&6)|((cpy>>cur)&(Z|1))|(2);
    int t=cur;
    do{
        if     (c==(Z|3)){cpx|=(T<<cur);cur=cur+1;}
        else if(c==(  7)){cpy|=(Y<<cur);cur=cur+G;}
        else if(c==(Z|5)){cpx|=(O<<cur);cur=cur-1;}
        else if(c==(Z|6)){cpy|=(O<<cur);cur=cur-G;}
        else {break;}
        if(cur==F){
           if(cpx & cpy & EE ){return;}
           break;
        }
        c=((cpx>>(cur-1))&6)|((cpy>>cur)&(Z|1));
    }while(1);

    cpx|=(O<<t);
    cur=t-1;
    if(!((cpx>>cur)&2)){mover(cur,cpx,cpy);}
    if(!((cpy>>cur)&Z)){moved(cur,cpx,cpy);}
    if(!((cpx>>cur)&1)){movel(cur,cpx,cpy);}
    if(!((cpy>>cur)&1)){moveu(cur,cpx,cpy);}
}
void moved(int cur,unsigned long long cpx,unsigned long long cpy){
    if(F==cur+G){
        count++;
        return;
    }

    int c=((cpx>>(cur-1))&6)|((cpy>>cur)&(Z|1))|(Z);
    int t=cur;
    do{
        if     (c==(Z|3)){cpx|=(T<<cur);cur=cur+1;}
        else if(c==(  7)){cpy|=(Y<<cur);cur=cur+G;}
        else if(c==(Z|5)){cpx|=(O<<cur);cur=cur-1;}
        else if(c==(Z|6)){cpy|=(O<<cur);cur=cur-G;}
        else {break;}
        if(cur==F){
           if(cpx & cpy & EE ){return;}
           break;
        }
        c=((cpx>>(cur-1))&6)|((cpy>>cur)&(Z|1));
    }while(1);

    cpy|=(Y<<t);
    cur=t+G;
    if(!((cpx>>cur)&2)){mover(cur,cpx,cpy);}
    if(!((cpy>>cur)&Z)){moved(cur,cpx,cpy);}
    if(!((cpx>>cur)&1)){movel(cur,cpx,cpy);}
    if(!((cpy>>cur)&1)){moveu(cur,cpx,cpy);}
}
void moveu(int cur,unsigned long long cpx,unsigned long long cpy){
    if(F==cur-G){
        count++;
        return;
    }

    int c=((cpx>>(cur-1))&6)|((cpy>>cur)&(Z|1))|(1);
    int t=cur;
    do{
        if     (c==(Z|3)){cpx|=(T<<cur);cur=cur+1;}
        else if(c==(  7)){cpy|=(Y<<cur);cur=cur+G;}
        else if(c==(Z|5)){cpx|=(O<<cur);cur=cur-1;}
        else if(c==(Z|6)){cpy|=(O<<cur);cur=cur-G;}
        else {break;}
        if(cur==F){
           if(cpx & cpy & EE ){return;}
           break;
        }
        c=((cpx>>(cur-1))&6)|((cpy>>cur)&(Z|1));
    }while(1);

    cpy|=(O<<t);
    cur=t-G;
    if(!((cpx>>cur)&2)){mover(cur,cpx,cpy);}
    if(!((cpy>>cur)&Z)){moved(cur,cpx,cpy);}
    if(!((cpx>>cur)&1)){movel(cur,cpx,cpy);}
    if(!((cpy>>cur)&1)){moveu(cur,cpx,cpy);}
}

int main(void){
    int i;
    //wall
    unsigned long long cpx=0;
    unsigned long long cpy=0;
    for(i=0;i<G;i++){cpx<<=G;cpx|=(1<<(G-1));}
    cpy=((O<<G)-1)<<(G*G)|((O<<G)-1);

    printf("start %llx:%llx\n",cpy,cpx);
    clock_t start = clock();    // start
    cpx<<=1;
    cpx|=3;
    cpy|=1<<G;

    mover(1,cpx,cpy);
    moved(1,cpx,cpy);
    //result
    clock_t end = clock();    // end
    printf("total=%d: time=%lf[sec]\n",count*2,(double)(end - start) / CLOCKS_PER_SEC);
}
