/**

����ͳһ����Ϸ���½ӿ�

**/

#define GameProcessInterface_HandleEnvent(p) p->HandleEnvent(p)
#define GameProcessInterface_UpdateData(p) p->UpdateData(p)
#define GameProcessInterface_Render(p) p->Render(p)


typedef void (* HandleEnventFun)( void* _this );
typedef void (* UpdateDataFun)( void* _this );
typedef void (* RenderFun)( void* _this );


