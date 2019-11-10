//#ifndef SERIALIZERS
//#define SERIALIZERS

//#include <string>
//#include <map>
//#include <boost/type_traits.hpp>
//#include <boost/fusion/include/sequence.hpp>
//#include <boost/foreach.hpp>
//#include <boost/fusion/adapted/struct/detail/extension.hpp>
//#include <boost/units/detail/utility.hpp>

////#include <boost/spirit/include/qi.hpp>
////#include <boost/spirit/include/phoenix.hpp>

//template<typename S>
//struct sequence
//{
//    // Point to the first element
//    typedef boost::mpl::int_<0> begin;

//    // Point to the element after the last element in the sequence
//    typedef typename boost::fusion::result_of::size<S>::type end;

//    // Point to the first element
//    typedef boost::mpl::int_<0> first;

//    // Point to the second element (for pairs)
//    typedef boost::mpl::int_<1> second;

//    // Point to the last element in the sequence
//    typedef typename boost::mpl::prior<end>::type last;

//    // Number of elements in the sequence
//    typedef typename boost::fusion::result_of::size<S>::type size;
//};

//template<typename S,
//         typename N>
//struct element_at
//{
//    // Type of the element at this index
//    typedef typename boost::fusion::result_of::value_at<S, N>::type type;

//    // Previous element
//    typedef typename boost::mpl::prior<N>::type previous;

//    // Next element
//    typedef typename boost::mpl::next<N>::type next;

//    // Member name of the element at this index
//    static inline std::string name(void)
//    {
//        return boost::fusion::extension::struct_member_name<S, N::value>::call();
//    }

//    // Type name of the element at this index
//    static inline std::string type_name(void)
//    {
//        return boost::units::detail::demangle(typeid(type).name());
//    }

//    // Access the element
//    static inline typename boost::fusion::result_of::at<S const, N>::type get(S const& s)
//    {
//        return boost::fusion::at<N>(s);
//    }
//};

//template<typename S,
//         typename N>
//struct separator
//{
//    static inline std::string comma()
//    {
//        return ",";
//    }
//};

//// Specialize on the last element and prevent a comma from being returned.
//template<typename S>
//struct separator<S, typename sequence<S>::last>
//{
//    static inline std::string comma()
//    {
//        return "";
//    }
//};


//template<typename S, typename N>
//struct struct_serializer_recursive
//{
//    // Get the current and next elements
//    typedef typename element_at<S, N>::type current_t;
//    typedef typename element_at<S, N>::next next_t;

//    template<typename Ostream>
//    static inline void serialize(Ostream& os, S const& s, int depth, bool, bool)
//    {
//        // The name of the element is the key
//        std::string name = element_at<S, N>::name();

//        // The element itself is the value
//        current_t const& t = element_at<S, N>::get(s);

//        // Output the key
//        os << "\n" + tab(depth) + "\""
//           << name
//           << "\" : ";

//        // Recursively output the value
//        json_serializer<current_t>::serialize(os, t, depth, false, false);

//        // Add a separator for the next element
//        // (Pay attention to this, we will revisit it later)
//        os << separator<S, N>::comma();

//        // Perform a recursive call to the next element
//        struct_serializer_recursive<S, next_t>::serialize(os, s, depth, false, false);
//    }
//};

//template<typename S>
//struct struct_serializer_recursive<S, typename sequence<S>::end>
//{
//    template<typename Ostream>
//    static inline void serialize(Ostream& os, S const& s, int depth, bool, bool)
//    {
//        // No output
//    }
//};

//// Initiate the recursion by calling into the first element
//template<typename S>
//struct struct_serializer_initiate : struct_serializer_recursive<S, typename sequence<S>::begin>
//{

//};


//// Helper method for generating a tab as 3 spaces
//static inline std::string tab(int depth)
//{
//    std::string retval;
//    for(int i = 0; i < depth; ++i){retval += "   ";}
//    return retval;
//}


//template<typename T>
//struct primitive_serializer
//{
//    typedef primitive_serializer<T> type;

//    template<typename Ostream>
//    static inline void serialize(Ostream& os, T const& t, int depth, bool array_value, bool)
//    {
//        // Put in tabs if this is a value from an array (called from an array serializer)
//        if(array_value)
//        {
//            os << "\n" + tab(depth) + "\""
//               << t
//               << "\"";
//        }
//        else
//        {
//            os << "\""
//               << t
//               << "\"";
//        }
//    }
//};


//template<typename T>
//struct array_serializer
//{
//    typedef array_serializer<T> type;

//    // If T is an array type then removes the top level array qualifier from T, otherwise leaves T unchanged.
//    // For example "int[2][3]" becomes "int[3]".
//    typedef typename boost::remove_bounds<T>::type slice_t;

//    // Determine the size of the array by dividing out the size of its elements
//    static const size_t size = sizeof(T) / sizeof(slice_t);

//    template<typename Ostream>
//    static inline void serialize(Ostream& os, T const& t, int depth, bool, bool)
//    {
//        // Indent the stream
//        os << "\n" + tab(depth) + "[";

//        // For each element in the array
//        for(unsigned int i = 0; i < size; ++i)
//        {
//            // Serialize the element
//            json_serializer<slice_t>::serialize(os, t[i], depth + 1);

//            // As long as we are not after the last element
//            if(i != size-1)
//            {
//                // Add a comma separator
//                os << ", ";
//            }
//        }

//        // Close the array representation
//        os << "\n" + tab(depth) + "]";
//    }
//};


//template<typename T>
//struct container_serializer
//{
//    typedef container_serializer<T> type;

//    template<typename Ostream>
//    static inline void serialize(Ostream& os, T const& t, int depth, bool, bool)
//    {
//        os << "\n" + tab(depth) + "[";

//        // Use the container's size method
//        std::size_t size = t.size();
//        std::size_t count = 0;

//        // STL containers all have a "value_type" typedef
//        BOOST_FOREACH(typename T::value_type const& v, t)
//        {
//            // Serialize each value
//            json_serializer<typename T::value_type>::serialize(os, v, depth + 1, true, false);

//            if(count != size - 1)
//            {
//                os << ", ";
//            }

//            // Keep track of the count so we can tell when a comma separator is needed
//            ++count;
//        }

//        os << "\n" + tab(depth) + "]";
//    }
//};

//template<typename T>
//struct struct_serializer
//{
//    typedef struct_serializer<T> type;

//    template<typename Ostream>
//    static inline void serialize(Ostream& os, T const& t, int depth, bool array_value)
//    {
//        // If being called from the std::map specialization of the container serializer,
//        // we should treat the values as pairs, so forward to the appropriate serializer
//        if(pair)
//        {
//           pair_serializer_initiate<T>::serialize(os, t, depth, false, false);
//        }
//        else
//        {
//           os << "\n" + tab(depth) + "{";
//           struct_serializer_initiate<T>::serialize(os, t, depth + 1, false, false);
//           os << "\n" + tab(depth) + "}";
//        }
//    }
//};

//template<typename T>
//struct choose_serializer
//{
//    // Very large typedef, indented to show the different nested levels
//    typedef
//    typename boost::mpl::eval_if<boost::is_array<T>,                                                                                      // If the type is an array,
//    boost::mpl::identity<array_serializer<T> >,                                                              // use the array serializer
//    typename boost::mpl::eval_if<boost::spirit::traits::is_container<T>,                                     // Otherwise, check to see if it is a container (using the hidden type-trait)
//    boost::mpl::identity<container_serializer<T> >,                             // If so, use the container serializer
//    typename boost::mpl::eval_if<boost::is_class<T>,                            // Otherwise, check to see if it is a structure
//    boost::mpl::identity<struct_serializer<T> >,   // If so, use the structure serializer
//    boost::mpl::identity<primitive_serializer<T> > // If all else fails, treat it as a primitive.
//    >
//    >
//    >::type
//    type;
//};

//// The json serializer adapts itself to the top level type
//template<typename T>
//struct json_serializer : public choose_serializer<T>::type
//{

//};

//// This is the mixin to inherit from
//template<typename T>
//struct json
//{
//    // Returns the json representation of this class
//    std::string to_json(void)
//    {
//        // Serialize to a stringstream, convert booleans to strings. Start at a depth of 0.
//        std::stringstream ss;
//        json_serializer<T>::serialize(ss << std::boolalpha, self(), 0);
//        return ss.str();
//    }

//private:

//    // Cast ourselves to the template parameter since this is a mixin via CRTP
//    T const& self(void) const
//    {
//        return *static_cast<T const*>(this);
//    }

//};


//template<typename K, typename V, typename C, typename A>
//struct container_serializer<std::map<K, V, C, A> >
//{
//    typedef std::map<K, V, C, A> T;
//    typedef container_serializer<T> type;

//    template<typename Ostream>
//    static inline void serialize(Ostream& os, T const& t, int depth, bool array_value)
//    {
//        os << "\n" + tab(depth) + "{";

//        std::size_t size = t.size();
//        std::size_t count = 0;

//        BOOST_FOREACH(typename T::value_type v, t)
//        {
//            // This will end up calling the structure serializer, but we set the "pair" flag to true
//            json_serializer<typename T::value_type>::serialize(os, v, depth + 1, true);

//            if(count != size - 1)
//            {
//                os << ", ";
//            }

//            ++count;
//        }

//        os << "\n" + tab(depth) + "}";
//    }
//};


//#endif // SERIALIZERS

