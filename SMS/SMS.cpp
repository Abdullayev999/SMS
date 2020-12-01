#include <iostream>
#include  <string>
#include <exception>
#include <memory>

 /*
 Задание 1: Рассылка писем
        Реализуйте следующий интерфейс для рассылки писем:
        Mailer mailer;
        mailer.setFrom("from@address.com");
        mailer.setSubject("subject...");
        mailer.addReceiver("mike@address.com");
        mailer.addReceiver("john@address.com");
        mailer.setMessage("message");
        mailer.send();

      + Если при вызове send отсутствует отправитель (не указан setFrom),
        тогда нужно бросить EmptyFromException
      + Если при вызове send нет ни единого получателя
        (для добавления получателя используется addReceiver),
        нужно бросить EmptyReceiverException
      + Если в случае вызова send() все прошло успешно, распечатайте полную
          информацию о сообщении и список получателей
    */
class Mail
{
public:
    Mail() :m_recervers(new std::string[m_size])
    {

    }

    void setFrom(const std::string& from)
    {
        m_from = from;
    }

    void setSubject(const std::string& subject)
    {
        m_subject = subject;
    }

    void addReceiver(const std::string& receiver)
    {
        if (m_index >= m_size)capacity();

        m_recervers[m_index++] = receiver;
    }

    void setMessage(const std::string& msg)
    {
        m_msg = msg;
    }

    void send()
    {
        if (m_from.empty()) {
            throw std::exception("Empty From Exception");
        }

        if (!m_index) {
            throw std::exception("Empty Receiver Exception");
        }
    }

private:

    friend std::ostream& operator<<(std::ostream& os, const Mail& n)
    {
        os << "Message from\t:\t" << n.m_from << " .\n";
        os << "Subject\t\t:\t" << n.m_subject << " .\n";

        os << "Receiver\t:\t";
        for (int i = 0; i < n.m_index; ++i) {
            os << n.m_recervers[i];
            if (i < n.m_index - 1)std::cout << " , ";
            else std::cout << " . ";
        }
        os << "\n\n----------------------------------------------------------------------------------------------\n";

        os << "Message\t:\n\n" << n.m_msg << '\n';
        return os;
    }

    void capacity()
    {
        m_size += m_capacity;

        std::string* tmp = new std::string[m_size];
        for (size_t i = 0; i < m_index; ++i)
        {
            tmp[i] = std::move(m_recervers[i]);
        }
        m_recervers.reset(tmp);
    }

    size_t m_size = 5;
    size_t m_capacity = 5;
    size_t m_index = 0;
    std::unique_ptr<std::string[]> m_recervers;
    std::string m_msg;
    std::string m_subject;
    std::string m_from;
};

int main()
{
    Mail mailer;
    mailer.addReceiver("f-abdullayev@mail.ru");
    mailer.addReceiver("cavid@gmail.com");
    mailer.setFrom("from@address.com");
    mailer.setSubject("Informaciya");
    mailer.addReceiver("mike@address.com");
    mailer.addReceiver("john@address.com");
    mailer.setMessage("Dear students\nHow are you ? I hope you are well!\nPlease send me all your mobile numbers and addresses.Our computer has burned out and we have lost your data.");


    try
    {
        mailer.send();
        std::cout << "Message send successful\n\n" << mailer << std::endl;
    }
    catch (std::exception& ex)
    {
        std::cout << ex.what();
    }
}

