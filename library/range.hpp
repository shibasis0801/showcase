struct range {
    int start, finish;
    int stride;

    range(int start, int finish) : start(start), finish(finish), stride(1) {}
    range(int start, int finish, int stride) : start(start), finish(finish), stride(stride) {}

    struct iterator;

    iterator begin() {
        return iterator(start, stride);
    }

    iterator end() {
        return iterator(finish, stride);
    }

    range step(int stride) {
        int offset;
        
        if (this->stride == 1 || stride == 1)
            offset = -1;

        return range(start, finish, offset + stride + this->stride);
    }

    struct iterator {
        
        int value;
        int step = 1;
        iterator(int value, int step) : value(value), step(step) {}

        iterator &operator=(int element) {
            value = element;
            return *this;
        }
        
        // Prefix
        iterator &operator++() {
            value += step;
            return *this;
        }

        // Postfix
        iterator operator++(int) {
            auto temp = iterator(value, this->step);
            value += step;
            return temp;
        }

        bool operator!=(const iterator &iter) {
            return value < iter.value;
        }

        int operator*() {
            return value;
        }
    };
};