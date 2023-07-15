#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <algorithm>
using namespace std;
int idOdd = 1, idEven = 0;
class Planes{
public:
    int id;
    int fuelLevel;
    int everyUnitTime;
    Planes(){             // for new Planes[7000] but will never happen
        id = -1;
        fuelLevel = -1;
        everyUnitTime = -1;
    }
    Planes(int _id,int _fuelLevel,int unitTime){
        id = _id;
        fuelLevel = _fuelLevel;
        everyUnitTime = unitTime;
    }
    Planes(int _id,int unitTime){
        id = _id;
        everyUnitTime = unitTime;
    } 
    void fuelUse(){
        fuelLevel--;         //after every timeUnit fuel--
    }
    void operator=(Planes d){
        id = d.id;
        fuelLevel = d.fuelLevel;
        everyUnitTime = d.everyUnitTime;
    }
    bool operator<(Planes c){
        return fuelLevel < c.fuelLevel;
    }

};
class queue:Planes{
public:
    Planes *num;
    int capacity;
    queue(){
        num = new Planes[7000];     //the maximum airplane 3*4*500;
        capacity = 0;
    }
    void PushAndCheckfuelLv(Planes p){
        num[capacity++] = p;
        sort(num, num+capacity);
    }
    Planes Pop(){
        Planes Q = num[0];
        for(int i=1;i<capacity;i++){
            num[i-1] = num[i];
        }
        capacity--;
        return Q;
    }
    void fuelReduce(){
        for(int i=0;i<capacity;i++){
            num[i].fuelUse();
        }
    }
};
/* void afterOneTimeUnit(queue *array){
    Planes fuel;
    fuel.fuelUse(array);
} */
int sortQueItem(queue *pArr,int num, Planes *l,int p, int *sizeQue){      // return empty queue[i]
        for(int i=0;i<3;i++){
            bool all_diff=1;
            int QueSize = pArr[i].capacity;
            for(int j=0;j<QueSize;j++){
                if(l[p].fuelLevel == pArr[i].num[j].fuelLevel){
                    all_diff = 0;
                }
            }
            if(all_diff) return i;
        }
        return 0;
}
int minNum(int *pArr, int num){    // landing queue only one plane in each queue
    int min = 0;                    // so we choose the min num first
    for(int i=0;i<num;i++){
        if(pArr[i]<pArr[min]){
            min = i;
        }
    }
    return min;
}
int main(){
    int timeUnit,planeInLanding,planeInTakeoff;
    int trueL = 0 ,trueT = 0;
    int num_E = 0;
    double sumTime_T = 0, sumTime_L = 0, sumFuel = 0;
    int sumL = 0, sumT = 0, sumC = 0, sumE = 0;
    Planes l[4],t[4],e[4],user[4];    // every unit time create plane and store
    queue takeOffQue[4],landingQue[3];
    int sizeOfQue_T[4] = {0},sizeofQue_L[3] = {0}; //the number plane in each queue
    bool isWork[4] = {false};
    srand((unsigned)time(NULL));
    cout << "How Many Time Unit You Want To Simulate:" ;
    cin >> timeUnit;
    for(int T=1;T<=timeUnit;T++){
        planeInLanding = rand()%5;    //0~4
        planeInTakeoff = rand()%5;    //0~4
        for(int i=0;i<planeInLanding;i++){
            sumL++;     //count the total plane
            Planes a(idOdd,rand()%10+1,T);
            idOdd+=2;
            l[i] = a;
            int whichQueueNumPush = sortQueItem(landingQue,3,l,i,sizeofQue_L);
            sizeofQue_L[whichQueueNumPush]++;
            landingQue[whichQueueNumPush].PushAndCheckfuelLv(a);
        }     //generate a plane and push to the queue_L
        for(int i=0;i<planeInTakeoff;i++){
            sumT++;       
            Planes a(idEven,T);
            idEven+=2;
            t[i] = a;
            int whichQueueNumPush = minNum(sizeOfQue_T,4);
            sizeOfQue_T[whichQueueNumPush]++;
            takeOffQue[whichQueueNumPush].PushAndCheckfuelLv(a);
        }   //generate a plane and push to the queue_T
        for(int i=0;i<3;i++){
            if(sizeofQue_L[i] == 0){
                continue;
            }
            while(sizeofQue_L[i]>0 && landingQue[i].num[0].fuelLevel == 0){
                Planes emergence = landingQue[i].Pop();
                num_E++;
                sumE ++;
                sizeofQue_L[i]--;
                if(num_E==1){
                    e[0] = emergence;
                    user[0] = emergence;
                    isWork[0] = true;
                    trueL++;
                }else if(num_E >1 && num_E<=4){
                    int temp = minNum(sizeOfQue_T,4);
                    e[num_E-1] = emergence;
                    user[temp] = emergence;
                    isWork[temp] = true;
                    trueL++;
                }
            }
        }
        if(num_E>4){
            sumC += num_E-4;
        }
        // 134~148 check emergence and calculate crash plane
        for(int i=0;i<4;i++){
            if(isWork[i]){
                continue;
            }
            else if(i!=0 && sizeofQue_L[i-1]!=0 && landingQue[i-1].num[0].fuelLevel>1){
                user[i] = landingQue[i-1].Pop();
                sizeofQue_L[i-1]--;
                isWork[i] = true;
                trueL++;
            }else if(sizeOfQue_T[i]>0 && takeOffQue[i].capacity!=0){
                user[i] = takeOffQue[i].Pop();
                sizeOfQue_T[i]--;
                isWork[i] = true;
                trueT++;
            }
        }  // normal situation
        for(int i=0;i<4;i++){
            if(isWork[i]){
                if(user[i].id % 2 == 0){
                    sumTime_T += T-user[i].everyUnitTime;
                }else if(user[i].id % 2 == 1){
                    sumTime_L += T-user[i].everyUnitTime;
                    sumFuel += user[i].fuelLevel;
                }
            }
        }
        cout << "This is time unit: " << T << endl;
        //1111111111111111111111111111111111111111111111111111111
        cout << "Step 1:" << endl;
        cout << "landing plane:";
        for(int i=0;i<3;i++){
            for(int j=0;j<landingQue[i].capacity;j++){
                cout << "(" << landingQue[i].num[j].id << "," << landingQue[i].num[j].fuelLevel << ")" << ",";
            }
        }
        for(int i=0;i<4;i++){
            if(user[i].id % 2 == 1){
                cout << "(" << user[i].id << "," << user[i].fuelLevel << ")" << ",";
            }
        }
        cout << endl;
        for(int i=1;i<=4;i++){
            cout << "Runway" << i << "(-1)" << endl;
            cout << "L: ";
            if(isWork[i-1]){
                if(user[i-1].id % 2 == 1){
                    cout << "(" << user[i-1].id << ", " << user[i-1].fuelLevel << ")";
                }
            }
            cout << endl;
            cout << "T: " << endl;
            cout << endl;
        }
        //22222222222222222222222222222222222222222222222
        cout << "Step 2: " << endl;
        cout << "takeoff plane:";
        for(int i=0;i<4;i++){
            for(int j=0;j<takeOffQue[i].capacity;j++){
                cout << "(" << takeOffQue[i].num[j].id << ")" << ",";
            }
        }
        for(int i=0;i<4;i++){
            if(user[i].id%2==0){
                cout << "(" << user[i].id << ")" << ",";
            }
        }
        cout << endl;
        for(int i=1;i<=4;i++){
            cout << "Runway" << i << "(-1)" << endl;
            if(isWork[i-1]){
                if(user[i-1].id % 2 == 1){
                    cout << "L: (" << user[i-1].id << ", " << user[i-1].fuelLevel << ")" << endl;
                    cout << "T:" << endl;
                }else if(user[i-1].id % 2 == 0){
                    cout<< "L:" << endl << "T: (" << user[i-1].id << ")" << endl;
                }
            }else cout << "L:" << endl << "T:" << endl;
        }
        cout << endl;
        //33333333333333333333333333333333333333333333333333333
        cout << "Step 3:" << endl;
        cout << "emergency plane:";
        for(int i=0;i<num_E;i++){
            if(num_E > 0){
                cout << "(" << e[i].id << "," << e[i].fuelLevel << ")" << ",";
            }
        }
        cout << endl;
        for(int i=1;i<=4;i++){
            cout << "Runway" << i << "(-1)" << endl;
            if(isWork[i-1]){
                if(user[i-1].id % 2 == 1){
                    cout << "L: (" << user[i-1].id << ", " << user[i-1].fuelLevel << ")" << endl;
                    cout << "T:" << endl;
                }else if(user[i-1].id % 2 == 0){
                    cout<< "L:" << endl << "T: (" << user[i-1].id << ")" << endl;
                }
            }else cout << "L:" << endl << "T:" << endl;
        }
        cout << endl;
        cout << "Step 4:" << endl;
        for(int i=0;i<4;i++){
            cout << "Runway" << i+1 << "(" << user[i].id << ")" << endl;
            cout << "L:" << endl;
            cout << "T:" << endl;
            cout << endl;
        }
        cout << "-------------------------------------" << endl; 
        for(int i=0;i<3;i++){
            landingQue[i].fuelReduce();
        }    // fuel reduce
        Planes initial(-1,-1,-1);
        num_E = 0;
        planeInLanding = 0;
        planeInTakeoff = 0;
        for(int i=0;i<4;i++){
            isWork[i] = {false};
            l[i] = initial;
            t[i] = initial;
            user[i] = initial;
            e[i] = initial; 
        }
        

    }
    cout << "average landing waiting time: " << fixed << setprecision(3) << sumTime_L/trueL << "(s)" << endl;
    cout << "average takeoff waiting time: " << fixed << setprecision(3) << sumTime_T/trueT << "(s)" << endl;
    cout << "average fuel saved: " << fixed << setprecision(3) << sumFuel/trueL << "(s)" << endl;
    cout << "total plane in emergency: " << sumE << endl;
    cout << "total plane crashed: " << sumC;
}
