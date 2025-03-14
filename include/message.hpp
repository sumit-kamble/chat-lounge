#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <iostream>
#include <string>
#include <cstring> // For memcpy, strncpy, snprintf
#include <cstdio>  // For snprintf

class Message
{
public:
    Message() : bodyLength_(0) {}

    // Use constexpr for constants
    static constexpr size_t maxBytes = 512;
    static constexpr size_t header = 4;

    // Parameterized constructor: packages the input message
    Message(const std::string &message)
    {
        bodyLength_ = getNewBodyLength(message.size());
        encodeHeader();
        memcpy(data + header, message.c_str(), bodyLength_);
    }

    // Ensure that the message body doesn't exceed the allowed size
    size_t getNewBodyLength(size_t newLength) const
    {
        return (newLength > maxBytes) ? maxBytes : newLength;
    }

    // Returns the entire data (header + body) as a string
    std::string getData() const
    {
        int length = header + bodyLength_;
        return std::string(data, length);
    }

    // Returns just the message body by stripping off the header
    std::string getBody() const
    {
        return std::string(data + header, bodyLength_);
    }

    // Decodes the header to retrieve the body length
    bool decodeHeader()
    {
        char new_header[header + 1] = "";
        strncpy(new_header, data, header);
        new_header[header] = '\0';
        int headervalue = atoi(new_header);
        if (headervalue > static_cast<int>(maxBytes) || headervalue < 0)
        {
            bodyLength_ = 0;
            return false;
        }
        bodyLength_ = static_cast<size_t>(headervalue);
        return true;
    }

    // Encodes the body length into the header
    void encodeHeader()
    {
        char new_header[header + 1] = "";
        // Format the body length as a 4-digit number, padded with zeros if needed
        snprintf(new_header, header + 1, "%04d", static_cast<int>(bodyLength_));
        memcpy(data, new_header, header);
    }

    size_t getBodyLength()
    {
        return bodyLength_;
    }

private:
    char data[header + maxBytes]; // Buffer to store header and body
    size_t bodyLength_;
};

#endif
