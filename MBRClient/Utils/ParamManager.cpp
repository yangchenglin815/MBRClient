#include "ParamManager.h"

ParamManager* ParamManager::m_instance = NULL;
ParamManager::ParamManager()
{
	
}

ParamManager::~ParamManager()
{
  
}

void ParamManager::loadFromDB()
{
	if (!m_paramItems.isEmpty())
	{
		return;
	}

	QSet<QString>::iterator it = m_necessaryParamKeys.begin();
	for (; it != m_necessaryParamKeys.end(); it++)
	{
		QMap<int, QString> paramsBySysCode;
		if (DBHELPER->m_pParameterTable->getParam(*it, paramsBySysCode))
		{
			m_paramItems.insert(*it, paramsBySysCode);
		}
	}
}

void ParamManager::getNecessaryParamKeys(QSet<QString>& paramKeys )
{
	paramKeys = m_necessaryParamKeys;
}

void ParamManager::initNecessaryParamKeys( QString faceAlgVersion, QString fveinAlgVersion, QString fprintAlgVersion)
{
	QString paramKey = "need_register_switch";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_NeedRegisterSwitch] = paramKey;

	paramKey = "info_supplement_switch";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_InfoSupplementSwitch] = paramKey;

	paramKey = "social_management_switch";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_SocialManagementSwitch] = paramKey;

	paramKey = "auto_addperson_switch";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_AutoAddpersonSwitch] = paramKey;

	paramKey = "voice_prompt_switch";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_VoicePromptSwitch] = paramKey;

	paramKey = "fingervein_supported";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_FingerveinSupported] = paramKey;

	paramKey = "fingerprint_supported";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_FingerprintSupported] = paramKey;

	paramKey = "biotype_support";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_BiotypeSupported] = paramKey;

	paramKey = QString::number(BioType_Face) + "_identification_method";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_FaceIdentificationMethod] = paramKey;

	paramKey = QString::number(BioType_FVein) + "_identification_method";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_FVeinIdentificationMethod] = paramKey;

	paramKey = QString::number(BioType_FPrint) + "_identification_method";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_FPrintIdentificationMethod] = paramKey;

	paramKey = QString::number(BioType_Face) + "_" + faceAlgVersion + "_quality_eval_switch";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_FaceQualityEvalSwitch] = paramKey;

	paramKey = "allow_createmodel";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_AllowCreatemodel] = paramKey;

	paramKey = "offline_createmodel_switch";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_OfflineCreatemodelSwitch] = paramKey;

	paramKey = QString::number(BioType_Face) + "_modelmaxfeatnum";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_FaceModelmaxfeatnum] = paramKey;

	paramKey = QString::number(BioType_Face) + "_modeltimeout";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_FaceModeltimeout] = paramKey;

	paramKey = QString::number(BioType_FVein) + "_modeltimeout";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_FVeinModeltimeout] = paramKey;

	paramKey = QString::number(BioType_FPrint) + "_modeltimeout";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_FPrintModeltimeout] = paramKey;

	paramKey = "max_model_count";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_FaceMaxModelCount] = paramKey;

	paramKey = "multi_angle_switch";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_FaceMultiAngleSwitch] = paramKey;

	paramKey = QString::number(BioType_Face) + "_" + faceAlgVersion + "_time_permotion";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_FaceTimePermotion] = paramKey;

	paramKey = "allow_identification";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_AllowIdentification] = paramKey;

	paramKey = "offline_identify_switch";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_OfflineIdentifySwitch] = paramKey;

	paramKey = QString::number(BioType_Face) + "_111_" + faceAlgVersion + "_recognition";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_VisRecognitionThresh] = paramKey;

	paramKey = QString::number(BioType_Face) + "_112_" + faceAlgVersion + "_recognition";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_NirRecognitionThresh] = paramKey;

	paramKey = QString::number(BioType_FVein) + "_121_" + fveinAlgVersion + "_recognition";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_FVeinRecognitionThresh] = paramKey;

	paramKey = QString::number(BioType_FPrint) + "_151_" + fprintAlgVersion + "_recognition";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_FPrintRecognitionThresh] = paramKey;

	paramKey = QString::number(BioType_Face) + "_" + faceAlgVersion + "_pic_float_threshold";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_FacePicFloatThreshold] = paramKey;

	paramKey = QString::number(BioType_Face) + "_identifynum";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_FaceIdentifynum] = paramKey;

	paramKey = QString::number(BioType_FVein) + "_identifynum";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_FVeinIdentifynum] = paramKey;

	paramKey = QString::number(BioType_FPrint) + "_identifynum";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_FPrintIdentifynum] = paramKey;

	paramKey = QString::number(BioType_FVein) + "_" + fveinAlgVersion + "_verifynum";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_FVeinVerifynum] = paramKey;

	paramKey = QString::number(BioType_FPrint) + "_" + fprintAlgVersion + "_verifynum";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_FPrintVerifynum] = paramKey;

	paramKey = QString::number(BioType_Face) + "_recogmaxfeatnum";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_FaceRecogmaxfeatnum] = paramKey;

	paramKey = QString::number(BioType_Face) + "_recogtimeout";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_FaceRecogtimeout] = paramKey;

	paramKey = QString::number(BioType_FVein) + "_recogtimeout";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_FVeinRecogtimeout] = paramKey;

	paramKey = QString::number(BioType_FPrint) + "_recogtimeout";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_FPrintRecogtimeout] = paramKey;

	paramKey = QString::number(BioType_Face) + "_" + faceAlgVersion + "_det_switch";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_FaceDetSwtich] = paramKey;

	paramKey = QString::number(BioType_Face) + "_" + faceAlgVersion + "_detlevel";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_FaceDetLevel] = paramKey;

	paramKey = QString::number(BioType_Face) + "_" + faceAlgVersion + "_det_times";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_FaceDetTimes] = paramKey;

	paramKey = QString::number(BioType_Face) + "_" + faceAlgVersion + "_det_recognition";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_FaceDetRecognition] = paramKey;

	paramKey = QString::number(BioType_Face) + "_" + faceAlgVersion + "_time_perdetmotion";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_FaceTimePerdetmotion] = paramKey;

	paramKey = "appeal_switch";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_AppealSwitch] = paramKey;

	paramKey = "appeal_pattern";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_AppealPattern] = paramKey;

	paramKey = QString::number(BioType_Face) + "_111_" + faceAlgVersion + "_appeal_recognition";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_VisAppealRecognition] = paramKey;

	paramKey = QString::number(BioType_Face) + "_112_" + faceAlgVersion + "_appeal_recognition";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_NirAppealRecognition] = paramKey;

	paramKey = "createmodel_outtime";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_Prompt_CreatemodelOuttime] = paramKey;

	paramKey = "createmodel_fail";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_Prompt_CreatemodelFail] = paramKey;

	paramKey = "createmodel_success";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_Prompt_CreatemodelSuccess] = paramKey;

	paramKey = "identify_det_fail";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_Prompt_IdentifyDetFail] = paramKey;

	paramKey = "identify_det_recognition_fail";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_Prompt_IdentifyDetRecognitionFail] = paramKey;

	paramKey = "identify_outtime";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_Prompt_IdentifyOuttime] = paramKey;

	paramKey = "identify_success";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_Prompt_IdentifySuccess] = paramKey;

	paramKey = "identify_recognition_fail";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_Prompt_IdentifyRecognitionFail] = paramKey;

	paramKey = "commit_appeal";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_Prompt_CommitAppeal] = paramKey;

	paramKey = "andy";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_Prompt_Andy] = paramKey;

	paramKey = "left_face";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_Prompt_LeftFace] = paramKey;

	paramKey = "right_face";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_Prompt_RightFace] = paramKey;

	paramKey = "looked_up";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_Prompt_LookedUp] = paramKey;

	paramKey = "bow";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_Prompt_Bow] = paramKey;

	paramKey = "open_mouth";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_Prompt_OpenMouth] = paramKey;

	paramKey = "blink";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_Prompt_Blink] = paramKey;

	paramKey = "add_staff_sync";
	m_necessaryParamKeys.insert(paramKey);
	m_paramKeyMap[Param_AddStaffSync] = paramKey;
}

QString ParamManager::getParam( int paramType, int sysCode )
{
	QString keyText = m_paramKeyMap[paramType];
	if (m_paramItems.contains(keyText) && m_paramItems[keyText].contains(sysCode))
	{
		return m_paramItems[keyText][sysCode];
	}
	else
	{
		return "";
	}
}


