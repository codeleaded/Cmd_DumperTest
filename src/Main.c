#include "/home/codeleaded/System/Static/Library/DumperMap.h"
#include "/home/codeleaded/System/Static/Container/Database.h"

void QueryLanguage_PrintDatabaseFunc(void* ptr,DB_Info* info){
    if(CStr_Cmp(info->tname,"CHAR")         && info->size==1)   printf("\t\'%c\'",*(char*)ptr);
    else if(CStr_Cmp(info->tname,"WCHAR")   && info->size==2)   printf("\t\'%lc\'",*(short*)ptr);
    else if(CStr_Cmp(info->tname,"BYTE")    && info->size==1)   printf("\t%d",*(char*)ptr);
    else if(CStr_Cmp(info->tname,"SHORT")   && info->size==2)   printf("\t%d",*(short*)ptr);
    else if(CStr_Cmp(info->tname,"INT")     && info->size==4)   printf("\t%d",*(int*)ptr);
    else if(CStr_Cmp(info->tname,"LONG")    && info->size==8)   printf("\t%ld",*(long*)ptr);
    else if(CStr_Cmp(info->tname,"FLOAT")   && info->size==4)   printf("\t%f",*(float*)ptr);
    else if(CStr_Cmp(info->tname,"DOUBLE")  && info->size==8)   printf("\t%lf",*(double*)ptr);
    else if(CStr_Cmp(info->tname,"STRING"))                     printf("\t\"%s\"",(char*)ptr);
    else                                                        printf("\tUNKOWN(%d)",info->size);
}

DumperMap Vector_DumperMap(Vector* v){
    D_Type ptr_type = D_Type_Array(v->SIZE,D_Type_New(v->ELEMENT_SIZE));

    DumperMap dm = DumperMap_Make((D_Type[]){
        D_Type_New(sizeof(int)),
        D_Type_New(sizeof(int)),
        D_Type_New(sizeof(int)),
        D_Type_New(sizeof(int)),
        D_Type_New(sizeof(long)),
        ptr_type,
        D_TYPE_END
    });
    return dm;
}

DumperMap Database_DumperMap(Database* ql){
    DumperMap dm = DumperMap_Make((D_Type[]){
        D_Type_New(sizeof(int)),
        Vector_DumperMap(&ql->typelist),
        Vector_DumperMap(&ql->types),
        Vector_DumperMap(&ql->data),
        D_TYPE_END
    });
    return dm;
}

int main(){

    //Vector v1 = Vector_New(sizeof(int));
    //Vector_Push(&v1,(int[]){ 1 });
    //Vector_Push(&v1,(int[]){ 2 });
    //Vector_Push(&v1,(int[]){ 3 });
    //Vector_Push(&v1,(int[]){ 4 });
    //Vector_Push(&v1,(int[]){ 5 });
    //Vector_Push(&v1,(int[]){ 6 });
    //Vector_Print(&v1);

    Database db1;
    Database_Read(&db1,"./db1.alxdb");
    
    //DumperMap dm = Vector_DumperMap(&v1);
    DumperMap dm = Database_DumperMap(&db1);

    DumperMap_Print(&dm);
    DumperMap_Write(&dm,"./Dump.alxd",&db1);

    //Vector v2;
    Database db2;
    DumperMap_Read(&dm,"./Dump.alxd",&db2);
    //Vector_Print(&v2);

    Database_Print(&db2,QueryLanguage_PrintDatabaseFunc);

    Database_Free(&db2);
    Database_Free(&db1);

    DumperMap_Free(&dm);

    return 0;
}