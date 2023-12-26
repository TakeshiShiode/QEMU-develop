// 以下の ifdef ブロックは、DLL からのエクスポートを容易にするマクロを作成するための
// 一般的な方法です。この DLL 内のすべてのファイルは、コマンド ラインで定義された SCIBLDCINTERRUPT_EXPORTS
// シンボルを使用してコンパイルされます。このシンボルは、この DLL を使用するプロジェクトでは定義できません。
// ソースファイルがこのファイルを含んでいる他のプロジェクトは、
// SCIBLDCINTERRUPT_API 関数を DLL からインポートされたと見なすのに対し、この DLL は、このマクロで定義された
// シンボルをエクスポートされたと見なします。
#ifdef SCIBLDCINTERRUPT_EXPORTS
#define SCIBLDCINTERRUPT_API __declspec(dllexport)
#else
#define SCIBLDCINTERRUPT_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

	void SciHandleInit(double *ret);
	void SciReqInt_BLDC(double *ret);

	void SciGetBLDC_PWM_U(double *ret);
	void SciGetBLDC_PWM_V(double *ret);
	void SciGetBLDC_PWM_W(double *ret);
	void SciSetBLDCData(double* pos, double* vdc, double* iu, double* iw, double* omega, double* ret);
#ifdef __cplusplus
}
#endif


#if 0
// このクラスは dll からエクスポートされました
class SCIBLDCINTERRUPT_API Cscibldcinterrupt {
public:
	Cscibldcinterrupt(void);
	// TODO: メソッドをここに追加します。
};

extern SCIBLDCINTERRUPT_API int nscibldcinterrupt;

SCIBLDCINTERRUPT_API int fnscibldcinterrupt(void);
#endif
