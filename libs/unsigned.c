#include "/home/codeleaded/System/Static/Library/AlxExternFunctions.h"
#include "/home/codeleaded/System/Static/Library/AXHDL.h"

/*
Token Unsigned_Unsigned_Handler_Ass(AXHDL* hdl,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);

    printf("[Unsigned]: ASS: %s = %s\n",a->str,b->str);

    if(b->tt==TOKEN_NUMBER){
        
    }else if(b->tt==TOKEN_STRING){
        
    }else{
        AXHDL_ErrorHandler(hdl,"Ass: Error -> %s has unsigned type!",b->str);
        return Token_Null();
    }
    return Token_Cpy(a);
}
Token Unsigned_Unsigned_Handler_Add(AXHDL* hdl,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);
    
    int realsize_a = AXHDL_TypeDrefPtrSize(hdl,a);
    CStr imm = Number_Get(realsize_a);
    Token ret = AXHDL_ExecuteP(hdl,a,b,op,"add","ADD","imul",imm,AXHDL_Function_Add,AXHDL_Function_Mul);
    CStr_Free(&imm);
    return ret;
}
Token Unsigned_Unsigned_Handler_Sub(AXHDL* hdl,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);
    
    int realsize_a = AXHDL_TypeDrefPtrSize(hdl,a);
    CStr imm = Number_Get(realsize_a);
    Token ret = AXHDL_ExecuteP(hdl,a,b,op,"sub","SUB","imul",imm,AXHDL_Function_Sub,AXHDL_Function_Mul);
    CStr_Free(&imm);
    return ret;
}
Token Unsigned_Unsigned_Handler_Equ(AXHDL* hdl,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);
    //return AXHDL_ExecuteCmp(hdl,a,b,op,"sete","EQU",AXHDL_Function_Equ);
    return AXHDL_ExecuteJmp(hdl,a,b,op,"jz","EQU",AXHDL_Function_Equ);
}
Token Unsigned_Null_Handler_Cast(AXHDL* hdl,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    return Token_By(TOKEN_CONSTSTRING_DOUBLE,"NONE");
}
Token Unsigned_Handler_Cast(AXHDL* hdl,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);

    if(op->str==NULL) return Unsigned_Null_Handler_Cast(hdl,op,args);
    return Token_Null();
}
*/

Token Unsigned_Unsigned_Handler_Dir(AXHDL* hdl,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);

    printf("[Unsigned]: Dir: %s = %s\n",a->str,b->str);

    AXHDL_Arch* aa = AXHDL_CurrentArch(hdl);
    if(!aa)                         AXHDL_ErrorHandler(hdl,"no arch found!");
    else if(a->tt != TOKEN_STRING)  AXHDL_ErrorHandler(hdl,"%s not a signal!",a->str);
    else if(b->tt != TOKEN_STRING)  AXHDL_ErrorHandler(hdl,"%s not a signal!",b->str);
    else{
        AXHDL_Signal_Dir a_dir = AXHDL_Arch_Pin_Dir(aa,a->str,&hdl->archs);
        AXHDL_Signal_Dir b_dir = AXHDL_Arch_Pin_Dir(aa,b->str,&hdl->archs);
        if(a_dir != AXHDL_SIGNAL_DIR_IN && a_dir != AXHDL_SIGNAL_DIR_INOUT)        AXHDL_ErrorHandler(hdl,"%s has dir %d!",a->str,a_dir);
        else if(b_dir != AXHDL_SIGNAL_DIR_OUT && b_dir != AXHDL_SIGNAL_DIR_INOUT)  AXHDL_ErrorHandler(hdl,"%s has dir %d!",b->str,b_dir);
        else{
            Vector_Push(&aa->wires,(AXHDL_Wire[]){ AXHDL_Wire_New(b->str,a->str) });
        }
    }

    return Token_Cpy(a);
}

Token Unsigned_Unsigned_Handler_And(AXHDL* hdl,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);
    
    printf("[Unsigned]: And: %s & %s\n",a->str,b->str);

    AXHDL_Arch* aa = AXHDL_CurrentArch(hdl);
    if(!aa)                         AXHDL_ErrorHandler(hdl,"no arch found!");
    else if(a->tt != TOKEN_STRING)  AXHDL_ErrorHandler(hdl,"%s not a signal!",a->str);
    else if(b->tt != TOKEN_STRING)  AXHDL_ErrorHandler(hdl,"%s not a signal!",b->str);
    else{
        AXHDL_Signal_Dir a_dir = AXHDL_Arch_Pin_Dir(aa,a->str,&hdl->archs);
        AXHDL_Signal_Dir b_dir = AXHDL_Arch_Pin_Dir(aa,b->str,&hdl->archs);
        if(a_dir != AXHDL_SIGNAL_DIR_OUT && a_dir != AXHDL_SIGNAL_DIR_INOUT)        AXHDL_ErrorHandler(hdl,"%s has dir %d!",a->str,a_dir);
        else if(b_dir != AXHDL_SIGNAL_DIR_OUT && b_dir != AXHDL_SIGNAL_DIR_INOUT)   AXHDL_ErrorHandler(hdl,"%s has dir %d!",b->str,b_dir);
        else{
            CStr sname = AXHDL_Stack_Next(hdl);
            CStr sname_a = AXHDL_Stack_Member(hdl,sname,"a");
            CStr sname_b = AXHDL_Stack_Member(hdl,sname,"b");
            CStr sname_c = AXHDL_Stack_Member(hdl,sname,"c");
            
            Vector_Push(&aa->chips,(AXHDL_Chip[]){ AXHDL_Chip_New("AND",sname) });
            Vector_Push(&aa->wires,(AXHDL_Wire[]){ AXHDL_Wire_New(a->str,sname_a) });
            Vector_Push(&aa->wires,(AXHDL_Wire[]){ AXHDL_Wire_New(b->str,sname_b) });
            
            CStr_Free(&sname_b);
            CStr_Free(&sname_a);
            CStr_Free(&sname);
            return Token_Move(TOKEN_STRING,sname_c);
        }
    }

    return Token_Null();
}
Token Unsigned_Unsigned_Handler_Or(AXHDL* hdl,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);
    
    printf("[Unsigned]: Or: %s | %s\n",a->str,b->str);

    AXHDL_Arch* aa = AXHDL_CurrentArch(hdl);
    if(!aa)                         AXHDL_ErrorHandler(hdl,"no arch found!");
    else if(a->tt != TOKEN_STRING)  AXHDL_ErrorHandler(hdl,"%s not a signal!",a->str);
    else if(b->tt != TOKEN_STRING)  AXHDL_ErrorHandler(hdl,"%s not a signal!",b->str);
    else{
        AXHDL_Signal_Dir a_dir = AXHDL_Arch_Pin_Dir(aa,a->str,&hdl->archs);
        AXHDL_Signal_Dir b_dir = AXHDL_Arch_Pin_Dir(aa,b->str,&hdl->archs);
        if(a_dir != AXHDL_SIGNAL_DIR_OUT && a_dir != AXHDL_SIGNAL_DIR_INOUT)        AXHDL_ErrorHandler(hdl,"%s has dir %d!",a->str,a_dir);
        else if(b_dir != AXHDL_SIGNAL_DIR_OUT && b_dir != AXHDL_SIGNAL_DIR_INOUT)   AXHDL_ErrorHandler(hdl,"%s has dir %d!",b->str,b_dir);
        else{
            CStr sname = AXHDL_Stack_Next(hdl);
            CStr sname_a = AXHDL_Stack_Member(hdl,sname,"a");
            CStr sname_b = AXHDL_Stack_Member(hdl,sname,"b");
            CStr sname_c = AXHDL_Stack_Member(hdl,sname,"c");
            
            Vector_Push(&aa->chips,(AXHDL_Chip[]){ AXHDL_Chip_New("OR",sname) });
            Vector_Push(&aa->wires,(AXHDL_Wire[]){ AXHDL_Wire_New(a->str,sname_a) });
            Vector_Push(&aa->wires,(AXHDL_Wire[]){ AXHDL_Wire_New(b->str,sname_b) });
            
            CStr_Free(&sname_b);
            CStr_Free(&sname_a);
            CStr_Free(&sname);
            return Token_Move(TOKEN_STRING,sname_c);
        }
    }

    return Token_Null();
}
Token Unsigned_Unsigned_Handler_Xor(AXHDL* hdl,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);
    
    printf("[Unsigned]: Xor: %s ^ %s\n",a->str,b->str);

    AXHDL_Arch* aa = AXHDL_CurrentArch(hdl);
    if(!aa)                         AXHDL_ErrorHandler(hdl,"no arch found!");
    else if(a->tt != TOKEN_STRING)  AXHDL_ErrorHandler(hdl,"%s not a signal!",a->str);
    else if(b->tt != TOKEN_STRING)  AXHDL_ErrorHandler(hdl,"%s not a signal!",b->str);
    else{
        AXHDL_Signal_Dir a_dir = AXHDL_Arch_Pin_Dir(aa,a->str,&hdl->archs);
        AXHDL_Signal_Dir b_dir = AXHDL_Arch_Pin_Dir(aa,b->str,&hdl->archs);
        if(a_dir != AXHDL_SIGNAL_DIR_OUT && a_dir != AXHDL_SIGNAL_DIR_INOUT)        AXHDL_ErrorHandler(hdl,"%s has dir %d!",a->str,a_dir);
        else if(b_dir != AXHDL_SIGNAL_DIR_OUT && b_dir != AXHDL_SIGNAL_DIR_INOUT)   AXHDL_ErrorHandler(hdl,"%s has dir %d!",b->str,b_dir);
        else{
            CStr sname = AXHDL_Stack_Next(hdl);
            CStr sname_a = AXHDL_Stack_Member(hdl,sname,"a");
            CStr sname_b = AXHDL_Stack_Member(hdl,sname,"b");
            CStr sname_c = AXHDL_Stack_Member(hdl,sname,"c");
            
            Vector_Push(&aa->chips,(AXHDL_Chip[]){ AXHDL_Chip_New("XOR",sname) });
            Vector_Push(&aa->wires,(AXHDL_Wire[]){ AXHDL_Wire_New(a->str,sname_a) });
            Vector_Push(&aa->wires,(AXHDL_Wire[]){ AXHDL_Wire_New(b->str,sname_b) });
            
            CStr_Free(&sname_b);
            CStr_Free(&sname_a);
            CStr_Free(&sname);
            return Token_Move(TOKEN_STRING,sname_c);
        }
    }

    return Token_Null();
}
Token Unsigned_Unsigned_Handler_Not(AXHDL* hdl,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    
    printf("[Unsigned]: Not: ~%s\n",a->str);

    AXHDL_Arch* aa = AXHDL_CurrentArch(hdl);
    if(!aa)                         AXHDL_ErrorHandler(hdl,"no arch found!");
    else if(a->tt != TOKEN_STRING)  AXHDL_ErrorHandler(hdl,"%s not a signal!",a->str);
    else{
        AXHDL_Signal_Dir a_dir = AXHDL_Arch_Pin_Dir(aa,a->str,&hdl->archs);
        if(a_dir != AXHDL_SIGNAL_DIR_OUT && a_dir != AXHDL_SIGNAL_DIR_INOUT)        AXHDL_ErrorHandler(hdl,"%s has dir %d!",a->str,a_dir);
        else{
            CStr sname = AXHDL_Stack_Next(hdl);
            CStr sname_a = AXHDL_Stack_Member(hdl,sname,"a");
            CStr sname_b = AXHDL_Stack_Member(hdl,sname,"b");
            
            Vector_Push(&aa->chips,(AXHDL_Chip[]){ AXHDL_Chip_New("NOT",sname) });
            Vector_Push(&aa->wires,(AXHDL_Wire[]){ AXHDL_Wire_New(a->str,sname_a) });
            
            CStr_Free(&sname_a);
            CStr_Free(&sname);
            return Token_Move(TOKEN_STRING,sname_b);
        }
    }

    return Token_Null();
}

Token Unsigned_Unsigned_Handler_Shl(AXHDL* hdl,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);
    
    printf("[Unsigned]: Shl: %s << %s\n",a->str,b->str);

    AXHDL_Arch* aa = AXHDL_CurrentArch(hdl);
    if(!aa)                         AXHDL_ErrorHandler(hdl,"no arch found!");
    else if(a->tt != TOKEN_STRING)  AXHDL_ErrorHandler(hdl,"%s not a signal!",a->str);
    else if(b->tt != TOKEN_STRING)  AXHDL_ErrorHandler(hdl,"%s not a signal!",b->str);
    else{
        AXHDL_Signal_Dir a_dir = AXHDL_Arch_Pin_Dir(aa,a->str,&hdl->archs);
        AXHDL_Signal_Dir b_dir = AXHDL_Arch_Pin_Dir(aa,b->str,&hdl->archs);
        if(a_dir != AXHDL_SIGNAL_DIR_OUT && a_dir != AXHDL_SIGNAL_DIR_INOUT)        AXHDL_ErrorHandler(hdl,"%s has dir %d!",a->str,a_dir);
        else if(b_dir != AXHDL_SIGNAL_DIR_OUT && b_dir != AXHDL_SIGNAL_DIR_INOUT)   AXHDL_ErrorHandler(hdl,"%s has dir %d!",b->str,b_dir);
        else{
            CStr sname = AXHDL_Stack_Next(hdl);
            CStr sname_a = AXHDL_Stack_Member(hdl,sname,"a");
            CStr sname_b = AXHDL_Stack_Member(hdl,sname,"b");
            CStr sname_c = AXHDL_Stack_Member(hdl,sname,"c");
            
            Vector_Push(&aa->chips,(AXHDL_Chip[]){ AXHDL_Chip_New("SHL",sname) });
            Vector_Push(&aa->wires,(AXHDL_Wire[]){ AXHDL_Wire_New(a->str,sname_a) });
            Vector_Push(&aa->wires,(AXHDL_Wire[]){ AXHDL_Wire_New(b->str,sname_b) });
            
            CStr_Free(&sname_b);
            CStr_Free(&sname_a);
            CStr_Free(&sname);
            return Token_Move(TOKEN_STRING,sname_c);
        }
    }

    return Token_Null();
}
Token Unsigned_Unsigned_Handler_Shr(AXHDL* hdl,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);
    
    printf("[Unsigned]: Shr: %s >> %s\n",a->str,b->str);

    AXHDL_Arch* aa = AXHDL_CurrentArch(hdl);
    if(!aa)                         AXHDL_ErrorHandler(hdl,"no arch found!");
    else if(a->tt != TOKEN_STRING)  AXHDL_ErrorHandler(hdl,"%s not a signal!",a->str);
    else if(b->tt != TOKEN_STRING)  AXHDL_ErrorHandler(hdl,"%s not a signal!",b->str);
    else{
        AXHDL_Signal_Dir a_dir = AXHDL_Arch_Pin_Dir(aa,a->str,&hdl->archs);
        AXHDL_Signal_Dir b_dir = AXHDL_Arch_Pin_Dir(aa,b->str,&hdl->archs);
        if(a_dir != AXHDL_SIGNAL_DIR_OUT && a_dir != AXHDL_SIGNAL_DIR_INOUT)        AXHDL_ErrorHandler(hdl,"%s has dir %d!",a->str,a_dir);
        else if(b_dir != AXHDL_SIGNAL_DIR_OUT && b_dir != AXHDL_SIGNAL_DIR_INOUT)   AXHDL_ErrorHandler(hdl,"%s has dir %d!",b->str,b_dir);
        else{
            CStr sname = AXHDL_Stack_Next(hdl);
            CStr sname_a = AXHDL_Stack_Member(hdl,sname,"a");
            CStr sname_b = AXHDL_Stack_Member(hdl,sname,"b");
            CStr sname_c = AXHDL_Stack_Member(hdl,sname,"c");
            
            Vector_Push(&aa->chips,(AXHDL_Chip[]){ AXHDL_Chip_New("SHR",sname) });
            Vector_Push(&aa->wires,(AXHDL_Wire[]){ AXHDL_Wire_New(a->str,sname_a) });
            Vector_Push(&aa->wires,(AXHDL_Wire[]){ AXHDL_Wire_New(b->str,sname_b) });
            
            CStr_Free(&sname_b);
            CStr_Free(&sname_a);
            CStr_Free(&sname);
            return Token_Move(TOKEN_STRING,sname_c);
        }
    }

    return Token_Null();
}

Token Unsigned_Unsigned_Handler_Add(AXHDL* hdl,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);
    
    printf("[Unsigned]: Add: %s + %s\n",a->str,b->str);

    AXHDL_Arch* aa = AXHDL_CurrentArch(hdl);
    if(!aa)                         AXHDL_ErrorHandler(hdl,"no arch found!");
    else if(a->tt != TOKEN_STRING)  AXHDL_ErrorHandler(hdl,"%s not a signal!",a->str);
    else if(b->tt != TOKEN_STRING)  AXHDL_ErrorHandler(hdl,"%s not a signal!",b->str);
    else{
        AXHDL_Signal_Dir a_dir = AXHDL_Arch_Pin_Dir(aa,a->str,&hdl->archs);
        AXHDL_Signal_Dir b_dir = AXHDL_Arch_Pin_Dir(aa,b->str,&hdl->archs);
        if(a_dir != AXHDL_SIGNAL_DIR_OUT && a_dir != AXHDL_SIGNAL_DIR_INOUT)        AXHDL_ErrorHandler(hdl,"%s has dir %d!",a->str,a_dir);
        else if(b_dir != AXHDL_SIGNAL_DIR_OUT && b_dir != AXHDL_SIGNAL_DIR_INOUT)   AXHDL_ErrorHandler(hdl,"%s has dir %d!",b->str,b_dir);
        else{
            CStr sname = AXHDL_Stack_Next(hdl);
            CStr sname_a = AXHDL_Stack_Member(hdl,sname,"a");
            CStr sname_b = AXHDL_Stack_Member(hdl,sname,"b");
            CStr sname_c = AXHDL_Stack_Member(hdl,sname,"c");
            
            Vector_Push(&aa->chips,(AXHDL_Chip[]){ AXHDL_Chip_New("ADD",sname) });
            Vector_Push(&aa->wires,(AXHDL_Wire[]){ AXHDL_Wire_New(a->str,sname_a) });
            Vector_Push(&aa->wires,(AXHDL_Wire[]){ AXHDL_Wire_New(b->str,sname_b) });
            
            CStr_Free(&sname_b);
            CStr_Free(&sname_a);
            CStr_Free(&sname);
            return Token_Move(TOKEN_STRING,sname_c);
        }
    }

    return Token_Null();
}
Token Unsigned_Unsigned_Handler_Sub(AXHDL* hdl,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);
    
    printf("[Unsigned]: Sub: %s - %s\n",a->str,b->str);

    AXHDL_Arch* aa = AXHDL_CurrentArch(hdl);
    if(!aa)                         AXHDL_ErrorHandler(hdl,"no arch found!");
    else if(a->tt != TOKEN_STRING)  AXHDL_ErrorHandler(hdl,"%s not a signal!",a->str);
    else if(b->tt != TOKEN_STRING)  AXHDL_ErrorHandler(hdl,"%s not a signal!",b->str);
    else{
        AXHDL_Signal_Dir a_dir = AXHDL_Arch_Pin_Dir(aa,a->str,&hdl->archs);
        AXHDL_Signal_Dir b_dir = AXHDL_Arch_Pin_Dir(aa,b->str,&hdl->archs);
        if(a_dir != AXHDL_SIGNAL_DIR_OUT && a_dir != AXHDL_SIGNAL_DIR_INOUT)        AXHDL_ErrorHandler(hdl,"%s has dir %d!",a->str,a_dir);
        else if(b_dir != AXHDL_SIGNAL_DIR_OUT && b_dir != AXHDL_SIGNAL_DIR_INOUT)   AXHDL_ErrorHandler(hdl,"%s has dir %d!",b->str,b_dir);
        else{
            CStr sname = AXHDL_Stack_Next(hdl);
            CStr sname_a = AXHDL_Stack_Member(hdl,sname,"a");
            CStr sname_b = AXHDL_Stack_Member(hdl,sname,"b");
            CStr sname_c = AXHDL_Stack_Member(hdl,sname,"c");
            
            Vector_Push(&aa->chips,(AXHDL_Chip[]){ AXHDL_Chip_New("SUB",sname) });
            Vector_Push(&aa->wires,(AXHDL_Wire[]){ AXHDL_Wire_New(a->str,sname_a) });
            Vector_Push(&aa->wires,(AXHDL_Wire[]){ AXHDL_Wire_New(b->str,sname_b) });
            
            CStr_Free(&sname_b);
            CStr_Free(&sname_a);
            CStr_Free(&sname);
            return Token_Move(TOKEN_STRING,sname_c);
        }
    }

    return Token_Null();
}
Token Unsigned_Unsigned_Handler_Mul(AXHDL* hdl,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);
    
    printf("[Unsigned]: Mul: %s * %s\n",a->str,b->str);

    AXHDL_Arch* aa = AXHDL_CurrentArch(hdl);
    if(!aa)                         AXHDL_ErrorHandler(hdl,"no arch found!");
    else if(a->tt != TOKEN_STRING)  AXHDL_ErrorHandler(hdl,"%s not a signal!",a->str);
    else if(b->tt != TOKEN_STRING)  AXHDL_ErrorHandler(hdl,"%s not a signal!",b->str);
    else{
        AXHDL_Signal_Dir a_dir = AXHDL_Arch_Pin_Dir(aa,a->str,&hdl->archs);
        AXHDL_Signal_Dir b_dir = AXHDL_Arch_Pin_Dir(aa,b->str,&hdl->archs);
        if(a_dir != AXHDL_SIGNAL_DIR_OUT && a_dir != AXHDL_SIGNAL_DIR_INOUT)        AXHDL_ErrorHandler(hdl,"%s has dir %d!",a->str,a_dir);
        else if(b_dir != AXHDL_SIGNAL_DIR_OUT && b_dir != AXHDL_SIGNAL_DIR_INOUT)   AXHDL_ErrorHandler(hdl,"%s has dir %d!",b->str,b_dir);
        else{
            CStr sname = AXHDL_Stack_Next(hdl);
            CStr sname_a = AXHDL_Stack_Member(hdl,sname,"a");
            CStr sname_b = AXHDL_Stack_Member(hdl,sname,"b");
            CStr sname_c = AXHDL_Stack_Member(hdl,sname,"c");
            
            Vector_Push(&aa->chips,(AXHDL_Chip[]){ AXHDL_Chip_New("MUL",sname) });
            Vector_Push(&aa->wires,(AXHDL_Wire[]){ AXHDL_Wire_New(a->str,sname_a) });
            Vector_Push(&aa->wires,(AXHDL_Wire[]){ AXHDL_Wire_New(b->str,sname_b) });
            
            CStr_Free(&sname_b);
            CStr_Free(&sname_a);
            CStr_Free(&sname);
            return Token_Move(TOKEN_STRING,sname_c);
        }
    }

    return Token_Null();
}
Token Unsigned_Unsigned_Handler_Div(AXHDL* hdl,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);
    
    printf("[Unsigned]: Div: %s / %s\n",a->str,b->str);

    AXHDL_Arch* aa = AXHDL_CurrentArch(hdl);
    if(!aa)                         AXHDL_ErrorHandler(hdl,"no arch found!");
    else if(a->tt != TOKEN_STRING)  AXHDL_ErrorHandler(hdl,"%s not a signal!",a->str);
    else if(b->tt != TOKEN_STRING)  AXHDL_ErrorHandler(hdl,"%s not a signal!",b->str);
    else{
        AXHDL_Signal_Dir a_dir = AXHDL_Arch_Pin_Dir(aa,a->str,&hdl->archs);
        AXHDL_Signal_Dir b_dir = AXHDL_Arch_Pin_Dir(aa,b->str,&hdl->archs);
        if(a_dir != AXHDL_SIGNAL_DIR_OUT && a_dir != AXHDL_SIGNAL_DIR_INOUT)        AXHDL_ErrorHandler(hdl,"%s has dir %d!",a->str,a_dir);
        else if(b_dir != AXHDL_SIGNAL_DIR_OUT && b_dir != AXHDL_SIGNAL_DIR_INOUT)   AXHDL_ErrorHandler(hdl,"%s has dir %d!",b->str,b_dir);
        else{
            CStr sname = AXHDL_Stack_Next(hdl);
            CStr sname_a = AXHDL_Stack_Member(hdl,sname,"a");
            CStr sname_b = AXHDL_Stack_Member(hdl,sname,"b");
            CStr sname_c = AXHDL_Stack_Member(hdl,sname,"c");
            
            Vector_Push(&aa->chips,(AXHDL_Chip[]){ AXHDL_Chip_New("DIV",sname) });
            Vector_Push(&aa->wires,(AXHDL_Wire[]){ AXHDL_Wire_New(a->str,sname_a) });
            Vector_Push(&aa->wires,(AXHDL_Wire[]){ AXHDL_Wire_New(b->str,sname_b) });
            
            CStr_Free(&sname_b);
            CStr_Free(&sname_a);
            CStr_Free(&sname);
            return Token_Move(TOKEN_STRING,sname_c);
        }
    }

    return Token_Null();
}
Token Unsigned_Unsigned_Handler_Neg(AXHDL* hdl,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    
    printf("[Unsigned]: Neg: -%s\n",a->str);

    AXHDL_Arch* aa = AXHDL_CurrentArch(hdl);
    if(!aa)                         AXHDL_ErrorHandler(hdl,"no arch found!");
    else if(a->tt != TOKEN_STRING)  AXHDL_ErrorHandler(hdl,"%s not a signal!",a->str);
    else{
        AXHDL_Signal_Dir a_dir = AXHDL_Arch_Pin_Dir(aa,a->str,&hdl->archs);
        if(a_dir != AXHDL_SIGNAL_DIR_OUT && a_dir != AXHDL_SIGNAL_DIR_INOUT)        AXHDL_ErrorHandler(hdl,"%s has dir %d!",a->str,a_dir);
        else{
            CStr sname = AXHDL_Stack_Next(hdl);
            CStr sname_a = AXHDL_Stack_Member(hdl,sname,"a");
            CStr sname_b = AXHDL_Stack_Member(hdl,sname,"b");
            
            Vector_Push(&aa->chips,(AXHDL_Chip[]){ AXHDL_Chip_New("NEG",sname) });
            Vector_Push(&aa->wires,(AXHDL_Wire[]){ AXHDL_Wire_New(a->str,sname_a) });
            
            CStr_Free(&sname_a);
            CStr_Free(&sname);
            return Token_Move(TOKEN_STRING,sname_b);
        }
    }

    return Token_Null();
}

Token Unsigned_Unsigned_Handler_Equ(AXHDL* hdl,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);
    
    printf("[Unsigned]: Equ: %s == %s\n",a->str,b->str);

    AXHDL_Arch* aa = AXHDL_CurrentArch(hdl);
    if(!aa)                         AXHDL_ErrorHandler(hdl,"no arch found!");
    else if(a->tt != TOKEN_STRING)  AXHDL_ErrorHandler(hdl,"%s not a signal!",a->str);
    else if(b->tt != TOKEN_STRING)  AXHDL_ErrorHandler(hdl,"%s not a signal!",b->str);
    else{
        AXHDL_Signal_Dir a_dir = AXHDL_Arch_Pin_Dir(aa,a->str,&hdl->archs);
        AXHDL_Signal_Dir b_dir = AXHDL_Arch_Pin_Dir(aa,b->str,&hdl->archs);
        if(a_dir != AXHDL_SIGNAL_DIR_OUT && a_dir != AXHDL_SIGNAL_DIR_INOUT)        AXHDL_ErrorHandler(hdl,"%s has dir %d!",a->str,a_dir);
        else if(b_dir != AXHDL_SIGNAL_DIR_OUT && b_dir != AXHDL_SIGNAL_DIR_INOUT)   AXHDL_ErrorHandler(hdl,"%s has dir %d!",b->str,b_dir);
        else{
            CStr sname = AXHDL_Stack_Next(hdl);
            CStr sname_a = AXHDL_Stack_Member(hdl,sname,"a");
            CStr sname_b = AXHDL_Stack_Member(hdl,sname,"b");
            CStr sname_c = AXHDL_Stack_Member(hdl,sname,"c");
            
            Vector_Push(&aa->chips,(AXHDL_Chip[]){ AXHDL_Chip_New("EQU",sname) });
            Vector_Push(&aa->wires,(AXHDL_Wire[]){ AXHDL_Wire_New(a->str,sname_a) });
            Vector_Push(&aa->wires,(AXHDL_Wire[]){ AXHDL_Wire_New(b->str,sname_b) });
            
            CStr_Free(&sname_b);
            CStr_Free(&sname_a);
            CStr_Free(&sname);
            return Token_Move(TOKEN_STRING,sname_c);
        }
    }

    return Token_Null();
}
Token Unsigned_Unsigned_Handler_Neq(AXHDL* hdl,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);
    
    printf("[Unsigned]: Neq: %s != %s\n",a->str,b->str);

    AXHDL_Arch* aa = AXHDL_CurrentArch(hdl);
    if(!aa)                         AXHDL_ErrorHandler(hdl,"no arch found!");
    else if(a->tt != TOKEN_STRING)  AXHDL_ErrorHandler(hdl,"%s not a signal!",a->str);
    else if(b->tt != TOKEN_STRING)  AXHDL_ErrorHandler(hdl,"%s not a signal!",b->str);
    else{
        AXHDL_Signal_Dir a_dir = AXHDL_Arch_Pin_Dir(aa,a->str,&hdl->archs);
        AXHDL_Signal_Dir b_dir = AXHDL_Arch_Pin_Dir(aa,b->str,&hdl->archs);
        if(a_dir != AXHDL_SIGNAL_DIR_OUT && a_dir != AXHDL_SIGNAL_DIR_INOUT)        AXHDL_ErrorHandler(hdl,"%s has dir %d!",a->str,a_dir);
        else if(b_dir != AXHDL_SIGNAL_DIR_OUT && b_dir != AXHDL_SIGNAL_DIR_INOUT)   AXHDL_ErrorHandler(hdl,"%s has dir %d!",b->str,b_dir);
        else{
            CStr sname = AXHDL_Stack_Next(hdl);
            CStr sname_a = AXHDL_Stack_Member(hdl,sname,"a");
            CStr sname_b = AXHDL_Stack_Member(hdl,sname,"b");
            CStr sname_c = AXHDL_Stack_Member(hdl,sname,"c");
            
            Vector_Push(&aa->chips,(AXHDL_Chip[]){ AXHDL_Chip_New("NEQ",sname) });
            Vector_Push(&aa->wires,(AXHDL_Wire[]){ AXHDL_Wire_New(a->str,sname_a) });
            Vector_Push(&aa->wires,(AXHDL_Wire[]){ AXHDL_Wire_New(b->str,sname_b) });
            
            CStr_Free(&sname_b);
            CStr_Free(&sname_a);
            CStr_Free(&sname);
            return Token_Move(TOKEN_STRING,sname_c);
        }
    }

    return Token_Null();
}
Token Unsigned_Unsigned_Handler_Grt(AXHDL* hdl,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);
    
    printf("[Unsigned]: Grt: %s > %s\n",a->str,b->str);

    AXHDL_Arch* aa = AXHDL_CurrentArch(hdl);
    if(!aa)                         AXHDL_ErrorHandler(hdl,"no arch found!");
    else if(a->tt != TOKEN_STRING)  AXHDL_ErrorHandler(hdl,"%s not a signal!",a->str);
    else if(b->tt != TOKEN_STRING)  AXHDL_ErrorHandler(hdl,"%s not a signal!",b->str);
    else{
        AXHDL_Signal_Dir a_dir = AXHDL_Arch_Pin_Dir(aa,a->str,&hdl->archs);
        AXHDL_Signal_Dir b_dir = AXHDL_Arch_Pin_Dir(aa,b->str,&hdl->archs);
        if(a_dir != AXHDL_SIGNAL_DIR_OUT && a_dir != AXHDL_SIGNAL_DIR_INOUT)        AXHDL_ErrorHandler(hdl,"%s has dir %d!",a->str,a_dir);
        else if(b_dir != AXHDL_SIGNAL_DIR_OUT && b_dir != AXHDL_SIGNAL_DIR_INOUT)   AXHDL_ErrorHandler(hdl,"%s has dir %d!",b->str,b_dir);
        else{
            CStr sname = AXHDL_Stack_Next(hdl);
            CStr sname_a = AXHDL_Stack_Member(hdl,sname,"a");
            CStr sname_b = AXHDL_Stack_Member(hdl,sname,"b");
            CStr sname_c = AXHDL_Stack_Member(hdl,sname,"c");
            
            Vector_Push(&aa->chips,(AXHDL_Chip[]){ AXHDL_Chip_New("GRT",sname) });
            Vector_Push(&aa->wires,(AXHDL_Wire[]){ AXHDL_Wire_New(a->str,sname_a) });
            Vector_Push(&aa->wires,(AXHDL_Wire[]){ AXHDL_Wire_New(b->str,sname_b) });
            
            CStr_Free(&sname_b);
            CStr_Free(&sname_a);
            CStr_Free(&sname);
            return Token_Move(TOKEN_STRING,sname_c);
        }
    }

    return Token_Null();
}
Token Unsigned_Unsigned_Handler_Les(AXHDL* hdl,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);
    
    printf("[Unsigned]: Les: %s < %s\n",a->str,b->str);

    AXHDL_Arch* aa = AXHDL_CurrentArch(hdl);
    if(!aa)                         AXHDL_ErrorHandler(hdl,"no arch found!");
    else if(a->tt != TOKEN_STRING)  AXHDL_ErrorHandler(hdl,"%s not a signal!",a->str);
    else if(b->tt != TOKEN_STRING)  AXHDL_ErrorHandler(hdl,"%s not a signal!",b->str);
    else{
        AXHDL_Signal_Dir a_dir = AXHDL_Arch_Pin_Dir(aa,a->str,&hdl->archs);
        AXHDL_Signal_Dir b_dir = AXHDL_Arch_Pin_Dir(aa,b->str,&hdl->archs);
        if(a_dir != AXHDL_SIGNAL_DIR_OUT && a_dir != AXHDL_SIGNAL_DIR_INOUT)        AXHDL_ErrorHandler(hdl,"%s has dir %d!",a->str,a_dir);
        else if(b_dir != AXHDL_SIGNAL_DIR_OUT && b_dir != AXHDL_SIGNAL_DIR_INOUT)   AXHDL_ErrorHandler(hdl,"%s has dir %d!",b->str,b_dir);
        else{
            CStr sname = AXHDL_Stack_Next(hdl);
            CStr sname_a = AXHDL_Stack_Member(hdl,sname,"a");
            CStr sname_b = AXHDL_Stack_Member(hdl,sname,"b");
            CStr sname_c = AXHDL_Stack_Member(hdl,sname,"c");
            
            Vector_Push(&aa->chips,(AXHDL_Chip[]){ AXHDL_Chip_New("LES",sname) });
            Vector_Push(&aa->wires,(AXHDL_Wire[]){ AXHDL_Wire_New(a->str,sname_a) });
            Vector_Push(&aa->wires,(AXHDL_Wire[]){ AXHDL_Wire_New(b->str,sname_b) });
            
            CStr_Free(&sname_b);
            CStr_Free(&sname_a);
            CStr_Free(&sname);
            return Token_Move(TOKEN_STRING,sname_c);
        }
    }

    return Token_Null();
}
Token Unsigned_Unsigned_Handler_Grq(AXHDL* hdl,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);
    
    printf("[Unsigned]: Grq: %s >= %s\n",a->str,b->str);

    AXHDL_Arch* aa = AXHDL_CurrentArch(hdl);
    if(!aa)                         AXHDL_ErrorHandler(hdl,"no arch found!");
    else if(a->tt != TOKEN_STRING)  AXHDL_ErrorHandler(hdl,"%s not a signal!",a->str);
    else if(b->tt != TOKEN_STRING)  AXHDL_ErrorHandler(hdl,"%s not a signal!",b->str);
    else{
        AXHDL_Signal_Dir a_dir = AXHDL_Arch_Pin_Dir(aa,a->str,&hdl->archs);
        AXHDL_Signal_Dir b_dir = AXHDL_Arch_Pin_Dir(aa,b->str,&hdl->archs);
        if(a_dir != AXHDL_SIGNAL_DIR_OUT && a_dir != AXHDL_SIGNAL_DIR_INOUT)        AXHDL_ErrorHandler(hdl,"%s has dir %d!",a->str,a_dir);
        else if(b_dir != AXHDL_SIGNAL_DIR_OUT && b_dir != AXHDL_SIGNAL_DIR_INOUT)   AXHDL_ErrorHandler(hdl,"%s has dir %d!",b->str,b_dir);
        else{
            CStr sname = AXHDL_Stack_Next(hdl);
            CStr sname_a = AXHDL_Stack_Member(hdl,sname,"a");
            CStr sname_b = AXHDL_Stack_Member(hdl,sname,"b");
            CStr sname_c = AXHDL_Stack_Member(hdl,sname,"c");
            
            Vector_Push(&aa->chips,(AXHDL_Chip[]){ AXHDL_Chip_New("GRQ",sname) });
            Vector_Push(&aa->wires,(AXHDL_Wire[]){ AXHDL_Wire_New(a->str,sname_a) });
            Vector_Push(&aa->wires,(AXHDL_Wire[]){ AXHDL_Wire_New(b->str,sname_b) });
            
            CStr_Free(&sname_b);
            CStr_Free(&sname_a);
            CStr_Free(&sname);
            return Token_Move(TOKEN_STRING,sname_c);
        }
    }

    return Token_Null();
}
Token Unsigned_Unsigned_Handler_Leq(AXHDL* hdl,Token* op,Vector* args){
    Token* a = (Token*)Vector_Get(args,0);
    Token* b = (Token*)Vector_Get(args,1);
    
    printf("[Unsigned]: Leq: %s <= %s\n",a->str,b->str);

    AXHDL_Arch* aa = AXHDL_CurrentArch(hdl);
    if(!aa)                         AXHDL_ErrorHandler(hdl,"no arch found!");
    else if(a->tt != TOKEN_STRING)  AXHDL_ErrorHandler(hdl,"%s not a signal!",a->str);
    else if(b->tt != TOKEN_STRING)  AXHDL_ErrorHandler(hdl,"%s not a signal!",b->str);
    else{
        AXHDL_Signal_Dir a_dir = AXHDL_Arch_Pin_Dir(aa,a->str,&hdl->archs);
        AXHDL_Signal_Dir b_dir = AXHDL_Arch_Pin_Dir(aa,b->str,&hdl->archs);
        if(a_dir != AXHDL_SIGNAL_DIR_OUT && a_dir != AXHDL_SIGNAL_DIR_INOUT)        AXHDL_ErrorHandler(hdl,"%s has dir %d!",a->str,a_dir);
        else if(b_dir != AXHDL_SIGNAL_DIR_OUT && b_dir != AXHDL_SIGNAL_DIR_INOUT)   AXHDL_ErrorHandler(hdl,"%s has dir %d!",b->str,b_dir);
        else{
            CStr sname = AXHDL_Stack_Next(hdl);
            CStr sname_a = AXHDL_Stack_Member(hdl,sname,"a");
            CStr sname_b = AXHDL_Stack_Member(hdl,sname,"b");
            CStr sname_c = AXHDL_Stack_Member(hdl,sname,"c");
            
            Vector_Push(&aa->chips,(AXHDL_Chip[]){ AXHDL_Chip_New("LEQ",sname) });
            Vector_Push(&aa->wires,(AXHDL_Wire[]){ AXHDL_Wire_New(a->str,sname_a) });
            Vector_Push(&aa->wires,(AXHDL_Wire[]){ AXHDL_Wire_New(b->str,sname_b) });
            
            CStr_Free(&sname_b);
            CStr_Free(&sname_a);
            CStr_Free(&sname);
            return Token_Move(TOKEN_STRING,sname_c);
        }
    }

    return Token_Null();
}

void Ex_Packer(ExternFunctionMap* Extern_Functions,Vector* funcs,AXHDL* hdl){ // Vector<CStr>
    TypeMap_PushContained(&hdl->types,funcs,
        Type_Make(AXHDL_TYPE_UNSIGNED,0UL,OperatorInterationMap_Make((OperatorInterater[]){
            OperatorInterater_Make((CStr[]){ NULL },OperatorDefineMap_Make((OperatorDefiner[]){
                OperatorDefiner_New(AXHDL_TOKEN_NOT,(Token(*)(void*,Token*,Vector*))Unsigned_Unsigned_Handler_Not),
                OperatorDefiner_New(AXHDL_TOKEN_NEG,(Token(*)(void*,Token*,Vector*))Unsigned_Unsigned_Handler_Neg),
                //OperatorDefiner_New(TOKEN_CAST,(Token(*)(void*,Token*,Vector*))Unsigned_Handler_Cast),
                //OperatorDefiner_New(TOKEN_AXHDL_SIZE,(Token(*)(void*,Token*,Vector*))Unsigned_Handler_Size),
                //OperatorDefiner_New(TOKEN_DESTROY,NULL),
                OPERATORDEFINER_END
            })),
            OperatorInterater_Make((CStr[]){ AXHDL_TYPE_UNSIGNED,NULL },OperatorDefineMap_Make((OperatorDefiner[]){
                OperatorDefiner_New(AXHDL_TOKEN_DIR,(Token(*)(void*,Token*,Vector*))Unsigned_Unsigned_Handler_Dir),

                OperatorDefiner_New(AXHDL_TOKEN_AND,(Token(*)(void*,Token*,Vector*))Unsigned_Unsigned_Handler_And),
                OperatorDefiner_New(AXHDL_TOKEN_OR, (Token(*)(void*,Token*,Vector*))Unsigned_Unsigned_Handler_Or),
                OperatorDefiner_New(AXHDL_TOKEN_XOR,(Token(*)(void*,Token*,Vector*))Unsigned_Unsigned_Handler_Xor),

                OperatorDefiner_New(AXHDL_TOKEN_SHL,(Token(*)(void*,Token*,Vector*))Unsigned_Unsigned_Handler_Shl),
                OperatorDefiner_New(AXHDL_TOKEN_SHR,(Token(*)(void*,Token*,Vector*))Unsigned_Unsigned_Handler_Shr),

                OperatorDefiner_New(AXHDL_TOKEN_ADD,(Token(*)(void*,Token*,Vector*))Unsigned_Unsigned_Handler_Add),
                OperatorDefiner_New(AXHDL_TOKEN_SUB,(Token(*)(void*,Token*,Vector*))Unsigned_Unsigned_Handler_Sub),
                OperatorDefiner_New(AXHDL_TOKEN_MUL,(Token(*)(void*,Token*,Vector*))Unsigned_Unsigned_Handler_Mul),
                OperatorDefiner_New(AXHDL_TOKEN_DIV,(Token(*)(void*,Token*,Vector*))Unsigned_Unsigned_Handler_Div),

                OperatorDefiner_New(AXHDL_TOKEN_EQU,(Token(*)(void*,Token*,Vector*))Unsigned_Unsigned_Handler_Equ),
                OperatorDefiner_New(AXHDL_TOKEN_NEQ,(Token(*)(void*,Token*,Vector*))Unsigned_Unsigned_Handler_Neq),
                OperatorDefiner_New(AXHDL_TOKEN_GRT,(Token(*)(void*,Token*,Vector*))Unsigned_Unsigned_Handler_Grt),
                OperatorDefiner_New(AXHDL_TOKEN_LES,(Token(*)(void*,Token*,Vector*))Unsigned_Unsigned_Handler_Les),
                OperatorDefiner_New(AXHDL_TOKEN_GRQ,(Token(*)(void*,Token*,Vector*))Unsigned_Unsigned_Handler_Grq),
                OperatorDefiner_New(AXHDL_TOKEN_LEQ,(Token(*)(void*,Token*,Vector*))Unsigned_Unsigned_Handler_Leq),
                OPERATORDEFINER_END
            })),
            OPERATORINTERATER_END
        }),
        (void(*)(Variable*))NULL,
        (void(*)(Variable*,Variable*))NULL)
    );
}
