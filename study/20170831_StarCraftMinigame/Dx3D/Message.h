#pragma once
#include "MessageTypes.h"
#include "cVariant.h"
#include <assert.h>
namespace Messaging {
	struct Message {
		Message(MessageTypes type) {

		}

		virtual ~Message() {

		}

		MessageTypes type;
	};

	template <typename MsgType>
	inline MsgType* ConvertMessageTo(Message* msg) {
#ifdef _DEBUG
		//dynamic_cast�� �̿��Ͽ� ��Ÿ�� Ÿ�� �˻� ����.
		MsgType* downcasted = dynamic_cast<MsgType*>(msg);
		assert(downcasted && "�߸��� Downcasting�Դϴ�.");
#elif
		//��������� ����? dynamic_cast��� RTTI üũ�� ���� static_cast�� �̿�
		//��� �߸��� ����ȯ�� ���� ������ ã�� �� ����.
		MsgType* downcasted = static_cast<MsgType*>(msg);
#endif
		return downcasted;
	}

}