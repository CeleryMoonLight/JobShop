/**
 * @brief Interface IOptimizer
 * 
 * @file optimizer.h
 * @author Jason Qiu
 * @date 2018-05-01
 */
#ifndef _OPTIMIZER_H_
#define _OPTIMIZER_H_

class IOptimizer {
public:
    IOptimizer() {}
    virtual ~IOptimizer() {}
private:
    IOptimizer(const IOptimizer &);
    IOptimizer &operator=(const IOptimizer &);
};

class GreedyOptimizer : public IOptimizer {

};

#endif /* end of _OPTIMIZER_H_ */
