#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MAX_TEXT_SIZE 300
#define IP_MAX_LENGTH 16 // 192.168.120.100 for example and a place for null terminator
#define IP_NUMBER_OF_DOTS 3
#define MIN_VALID_PORT 1024
#define NUMBER_OF_ARGS_CLIENT 3
#define NUMBER_OF_ARGS_SERVER 2

using client_id_t  = uint32_t;

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define DEBUG_LINE(f_, ...) printf((f_), ##__VA_ARGS__) // for debug usage

enum class EipErrors
{
    BadParameters,
    ToMuchSegments,
    ToFewSegments,
    SegmentNotValid,
    InvalidCharacters
};

enum class EportErrors
{
    UnvalidPort,
    //PortInUse
};

bool check_segment(char*, size_t);

bool is_valid_ip_address(char* ip_address, size_t length, EipErrors& o_err)
{
    if (ip_address == nullptr || length > IP_MAX_LENGTH)
    {
        o_err = EipErrors::BadParameters;
        return false;
    }

    size_t number_of_dots = 0;
    size_t current_segment_length = 0;
    for (size_t i = 0; i < length; i++)
    {
        if (ip_address[i] <= '9' && ip_address[i] >= '0')
        {
            current_segment_length++;
        }
        else if (ip_address[i] == '.')
        {
            number_of_dots++;
            if (number_of_dots > IP_NUMBER_OF_DOTS)
            {
                o_err = EipErrors::ToMuchSegments;
                return false;
            }
            
            if (!check_segment(ip_address + i - current_segment_length, current_segment_length))
            {
                o_err = EipErrors::SegmentNotValid;
                return false;
            }

            current_segment_length = 0;
        }
        else
        {
            o_err = EipErrors::InvalidCharacters;
            return false;
        }
    }

    if (!check_segment(ip_address + length - current_segment_length, current_segment_length)) // Check last segment
    {
        o_err = EipErrors::SegmentNotValid;
        return false;
    }

    if (number_of_dots < IP_NUMBER_OF_DOTS)
    {
        o_err = EipErrors::ToFewSegments;
        return false;
    }
    
    return true;
}

bool is_valid_port(uint16_t port_num, EportErrors& o_err)
{
    if (port_num < MIN_VALID_PORT)
    {
        o_err = EportErrors::UnvalidPort;
        return false;
    }

    return true;
}

void print_ip_error(EipErrors err)
{
    switch (err)
    {
        case EipErrors::BadParameters :
        {
            printf("At least one parameter to the function was bad/corrupted..\n");
            printf("Make sure that the array is not NULL and that length is of valid ip length\n");
            break;
        }

        case EipErrors::ToMuchSegments :
        {
            printf("To much ip segments..\n");
            break;
        }

        case EipErrors::ToFewSegments :
        {
            printf("To few ip segments..\n");
            break;
        }

        case EipErrors::SegmentNotValid :
        {
            printf("At least one segment is not valid..\n");
            break;
        }

        case EipErrors::InvalidCharacters :
        {
            printf("Ip address was entered with undefined charecter.\n");
            break;
        }
        
        default:
        {
            printf("Undefined IP error!\n");
            break;
        }
    }

    printf("The format of a valid ip is as followed: ZZX.ZZX.ZZX.ZZX\n");
    printf("Where Z is optional and ZZX is not grater then 255\n");
}

void print_port_error(EportErrors err)
{
    switch (err)
    {
        case EportErrors::UnvalidPort :
        {
            printf("Invalid port\n");
            break;
        }

        //case EportErrors::PortInUSE : // for future use..
        
        default:
        {
            printf("Undefined IP error!\n");
            break;
        }
    }

    printf("Valid port number is between 1024 to 65535\n");
}

bool check_segment(char* segment_start, size_t current_segment_length)
{
    if (current_segment_length == 0 || current_segment_length > 3)
    {
        return false;
    }
    
    char ip_segment[current_segment_length + 1] = {0}; // Place for null terminator and initialized..
    memcpy(ip_segment, segment_start, current_segment_length);
    int segment = atoi(ip_segment);
    if (segment < 0 || segment > 255) // valid segment is between 0 to 255.
    {
        return false;
    }

    return true;
}