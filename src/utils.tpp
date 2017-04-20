#include<vector>
#include<utility>

template<typename T>
std::vector<T> pair_to_vector(std::pair<T, T> p){
    return {p.first, p.second};
}

template<typename T>
std::vector<T> filter(bool (*pred)(T), std::vector<T> vec){
    std::vector<T> out;
    for(auto e:vec){
        if(pred(e)){
	    out.push_back(e);
	}
    }

    return out;
}

template<typename T>
void inplace_filter(bool (*pred)(T), std::vector<T> & vec){
    int pos = 0;
    for(auto e:vec){
	if(pred(e)){
	    vec[pos++] = e;
	}
    }
    vec.resize(pos);
}

template<typename A, typename B>
std::vector<B> map(std::function<B(A)> func, const std::vector<A> & vec){
    std::vector<B> out;
    for(auto e:vec){
	out.push_back(func(e));
    }
    return out;
}
