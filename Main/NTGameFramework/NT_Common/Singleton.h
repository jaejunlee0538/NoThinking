#pragma once
#include <assert.h>
namespace qwer {
	template <typename T>
	class Singleton
	{
	private:
		//����, ���� ���� ����
		Singleton(const Singleton<T>&) {}
		Singleton& operator=(const Singleton<T>&) {}
	public:
		Singleton();
		~Singleton();

		static T& GetSingleton();
	protected:
		static T* m_pSingleton;
	};

	template <typename T>
	T* Singleton<T>::m_pSingleton = nullptr;

	template<typename T>
	Singleton<T>::Singleton()
	{
		assert(m_pSingleton == nullptr && "�̱��� ��ü�� �ϳ��� ������ �� �ֽ��ϴ�");
		m_pSingleton = static_cast<T*>(this);
	}

	template<typename T>
	Singleton<T>::~Singleton()
	{
		m_pSingleton = nullptr;
	}

	template<typename T>
	T & Singleton<T>::GetSingleton()
	{
		assert(m_pSingleton != nullptr);
		return *m_pSingleton;
	}
}

#define STATIC_SINGLETON(CLASS)	\
private:\
	CLASS(){}\
	~CLASS(){}\
	CLASS(const CLASS&){}\
public:\
	static CLASS& GetSingleton(){\
		static CLASS instance;	\
		return instance;\
	}\
private: