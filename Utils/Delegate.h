#pragma once
#include <vector>

using std::vector;

namespace Engine
{
	namespace Events
	{
		// Unsafe generic delegate reference. Used to store a pointer to a delegate of unknown parameters
		class GenericDelegate
		{
		public:
			// Can be used to invoke operator() without casting to derived type.
			virtual void Invoke0P() = 0;
			virtual void Invoke1P(void*) = 0;
			virtual void Invoke2P(void*, void*) = 0;

			virtual ~GenericDelegate() {}

		};
		// Delegates of maximum 3 parameters
		template<class T, typename P1 = void, typename P2 = void >
		class Delegate : public GenericDelegate
		{
		private:
			// Delegates should be destroyed before the instance is destroyed.
			T* pInstance;
			// Stores a delegate list on a certain instance.
			vector<void (T::*)(P1, P2)> pFunctions;
		public:
			Delegate(T* t)
				:
				pInstance(t),
				pFunctions()
			{
			}
			~Delegate(){}

			void operator +=(void (T::*func)(P1, P2))
			{
				pFunctions.push_back(func);
			}
			void operator -=(void (T::*func)(P1, P2))
			{
				bool found = false;
				unsigned int i = 0;

				for (; i < pFunctions.size(); i++)
				{
					if (pFunctions[i] == func)
					{
						found = true;
						break;
					}
				}

				if (!found)
					throw std::runtime_error("Cannot perform operator-= as the delegate list does not contain the parameter.");
				else
					pFunctions.erase(pFunctions.begin + i);
			}
			void operator =(void (T::*func)(P1, P2))
			{
				pFunctions.clear();
				*this += func;
			}

			void operator()(P1 p1, P2 p2)
			{
				for (void (T::*func)(P1, P2) : pFunctions)
				{
					(pInstance->*(func))(p1,p2);
				}
			}

			void Invoke0P() override
			{

			}
			void Invoke1P(void* p1) override
			{

			}
			void Invoke2P(void* p1, void* p2) override
			{
				operator()(*static_cast<P1>(p1), *static_cast<P2>(p2));
			}

		};

		template<class T>
		class Delegate<T, void, void> : public GenericDelegate
		{
		private:
			T* pInstance;
			vector<void (T::*)(void)> pFunctions;
		public:
			Delegate(T* t)
				:
				pInstance(t),
				pFunctions()
			{
			}
			~Delegate() {}

			void operator +=(void (T::*func)(void))
			{
				pFunctions.push_back(func);
			}
			void operator -=(void (T::*func)(void))
			{
				bool found = false;
				unsigned int i = 0;

				for (; i < pFunctions.size(); i++)
				{
					if (pFunctions[i] == func)
					{
						found = true;
						break;
					}
				}

				if (!found)
					throw std::runtime_error("Cannot perform operator-= as the delegate list does not contain the parameter.");
				else
					pFunctions.erase(pFunctions.begin + i);
			}
			void operator =(void (T::*func)(void))
			{
				pFunctions.clear();
				*this += func;
			}

			void operator()()
			{
				for (void (T::*func)(void) : pFunctions)
				{
					(pInstance->*(func))();
				}
			}

			void Invoke0P() override
			{
				operator()();
			}
			void Invoke1P(void* p1) override
			{
			}
			void Invoke2P(void* p1, void* p2) override
			{
			}

		};

		template<class T, typename P1>
		class Delegate<T, P1, void> : public GenericDelegate
		{
		private:
			T* pInstance;
			vector<void (T::*)(P1)> pFunctions;
		public:
			Delegate(T* t)
				:
				pInstance(t),
				pFunctions()
			{
			}
			~Delegate() {}

			void operator +=(void (T::*func)(P1))
			{
				pFunctions.push_back(func);
			}
			void operator -=(void (T::*func)(P1))
			{
				bool found = false;
				unsigned int i = 0;

				for (; i < pFunctions.size(); i++)
				{
					if (pFunctions[i] == func)
					{
						found = true;
						break;
					}
				}

				if (!found)
					throw std::runtime_error("Cannot perform operator-= as the delegate list does not contain the parameter.");
				else
					pFunctions.erase(pFunctions.begin + i);
			}
			void operator =(void (T::*func)(P1))
			{
				pFunctions.clear();
				*this += func;
			}

			void operator()(P1 p1)
			{
				for (void (T::*func)(P1) : pFunctions)
				{
					(pInstance->*(func))(p1);
				}
			}

			void Invoke0P() override
			{
			}
			void Invoke1P(void* p1) override
			{
				operator()(*static_cast<P1*>(p1));
			}
			void Invoke2P(void* p1, void* p2) override
			{
			}
		};

	}
}