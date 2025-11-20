#include "/home/codeleaded/System/Static/Library/DumperMap.h"


DumperMap Vector_DumperMap(Vector* v){
    DumperMap dm = DumperMap_Make((D_Type[]){
        D_Type_New(sizeof(int)),
        D_Type_New(sizeof(int)),
        D_Type_New(sizeof(int)),
        D_Type_New(sizeof(int)),
        D_Type_Array(v->SIZE,D_Type_New(v->ELEMENT_SIZE)),
        D_TYPE_END
    });
    return dm;
}

int main(){

    Vector v1 = Vector_New(sizeof(int));
    Vector_Push(&v1,(int[]){ 1 });
    Vector_Push(&v1,(int[]){ 2 });
    Vector_Push(&v1,(int[]){ 3 });
    Vector_Push(&v1,(int[]){ 4 });
    Vector_Push(&v1,(int[]){ 5 });
    Vector_Push(&v1,(int[]){ 6 });
    Vector_Print(&v1);

    DumperMap dm = Vector_DumperMap(&v1);
    DumperMap_Print(&dm);
    DumperMap_Write(&dm,"./data/Vector.alxd",&v1);

    Vector v2;
    DumperMap_Read(&dm,"./data/Vector.alxd",&v2);
    Vector_Print(&v2);

    Vector_Free(&v2);
    Vector_Free(&v1);

    return 0;
}