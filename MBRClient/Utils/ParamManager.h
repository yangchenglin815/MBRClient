#ifndef __PARAMMANAGER_H__
#define __PARAMMANAGER_H__

#include <QString>
#include <QVector>
#include <QSet>
#include <QMap>
#include "DefineData.h"
#include "EnumData.h"

enum ParamType
{
	Param_NeedRegisterSwitch, //注册开关
	Param_InfoSupplementSwitch, //全民参保信息开关
	Param_SocialManagementSwitch, //社会化管理开关
	Param_AutoAddpersonSwitch, //自动添加参保人开关

	//Param_AAC058, //证件类型 //AZE102 生物类型 //AZE103 模板类型 	//AZE012 比对结果（成功、失败）

	Param_VoicePromptSwitch, //语音提示开关
	Param_FingerveinSupported, //指静脉手指
	Param_FingerprintSupported, //指纹手指

	Param_BiotypeSupported, //支持的生物类型
	Param_FaceIdentificationMethod, //人脸认证方式（1、前端  2、后端）
	Param_FVeinIdentificationMethod, //指静脉认证方式（1、前端  2、后端）
	Param_FPrintIdentificationMethod, //指纹认证方式（1、前端  2、后端）
	Param_FaceQualityEvalSwitch, //质量评估开关
	Param_AllowCreatemodel, //允许建模
	Param_OfflineCreatemodelSwitch, //离线建模开关
	Param_FaceModelmaxfeatnum, //人脸建模照片数
	Param_FaceModeltimeout, //人脸建模超时
	Param_FVeinModeltimeout, //指静脉建模超时
	Param_FPrintModeltimeout, //指纹建模超时
	Param_FaceMaxModelCount, //人脸最大基础模板数
	Param_FaceMultiAngleSwitch, //人脸多角度开关
	Param_FaceTimePermotion, //人脸多角度单个动作时间

	Param_AllowIdentification, //允许认证
	Param_OfflineIdentifySwitch, //离线认证开关
	Param_VisRecognitionThresh, //可见光认证阈值
	Param_NirRecognitionThresh, //近红外认证阈值
	Param_FVeinRecognitionThresh, //指静脉认证阈值
	Param_FPrintRecognitionThresh, //指纹认证阈值
	Param_FacePicFloatThreshold, //人脸认证照片浮动阈值
	Param_FaceIdentifynum, //人脸认证尝试次数
	Param_FVeinIdentifynum, //指静脉认证尝试次数
	Param_FPrintIdentifynum, //指纹认证尝试次数
	Param_FVeinVerifynum, //指静脉认证尝试次数
	Param_FPrintVerifynum, //指纹认证尝试次数
	Param_FaceRecogmaxfeatnum, //人脸认证尝试次数
	Param_FaceRecogtimeout, //人脸认证超时时间
	Param_FVeinRecogtimeout, //指静脉认证超时时间
	Param_FPrintRecogtimeout, //指纹认证超时时间
	Param_FaceDetSwtich, //人脸活体检测开关
	Param_FaceDetLevel, //人脸活体检测级别
	Param_FaceDetTimes, //人脸活体检测次数
	Param_FaceDetRecognition, //人脸活体检测阈值
	Param_FaceTimePerdetmotion, //人脸活体检测每个动作时间
	Param_AppealSwitch, //申诉开关
	Param_AppealPattern, //申诉方式
	Param_VisAppealRecognition, //可见光申诉阈值
	Param_NirAppealRecognition, //近红外申诉阈值

	Param_Prompt_CreatemodelOuttime, //【提示】建模超时
	Param_Prompt_CreatemodelFail, //【提示】建模失败
	Param_Prompt_CreatemodelSuccess, //【提示】建模成功
	Param_Prompt_IdentifyDetFail, //【提示】活体失败
	Param_Prompt_IdentifyDetRecognitionFail, //【提示】认证失败 + 活体失败
	Param_Prompt_IdentifyOuttime, //【提示】认证超时
	Param_Prompt_IdentifySuccess, //【提示】认证成功
	Param_Prompt_IdentifyRecognitionFail, //【提示】认证失败
	Param_Prompt_CommitAppeal, //【提示】提交申诉

	Param_Prompt_Andy, //【提示】正脸
	Param_Prompt_LeftFace, //【提示】左侧脸
	Param_Prompt_RightFace, //【提示】右侧脸
	Param_Prompt_LookedUp, //【提示】抬头
	Param_Prompt_Bow, //【提示】低头
	Param_Prompt_OpenMouth, //【提示】张口
	Param_Prompt_Blink, //【提示】眨眼

	Param_AddStaffSync, //参保人员同步数据开关
};

#define PARAMMANAGER ParamManager::getInstance()
class ParamManager
{
public:
	static ParamManager* getInstance()
	{
		if (m_instance == NULL)
		{
			m_instance = new ParamManager;
		}
		return m_instance;
	}

	static void releaseInstance()
	{
		safeDelete(m_instance);
	}

	QString getParam(int paramType, int sysCode);
	void getNecessaryParamKeys(QSet<QString>& paramKeys);
	void initNecessaryParamKeys( QString faceAlgVersion, QString fveinAlgVersion, QString fprintAlgVersion);
	void loadFromDB();

private:
	static ParamManager* m_instance;
	ParamManager();
	~ParamManager();

private:	
	QMap<int, QString> m_paramKeyMap;
	QSet<QString> m_necessaryParamKeys;
	QMap<QString, QMap<int, QString> > m_paramItems;
};

#endif
