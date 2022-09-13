#ifndef PROBLEM_H
#define PROBLEM_H

class Fraction
{
	public:
		Fraction();
	
		void setnum(void);
    	void setden(const int);
    	void setwhole(const int);
    	void setsign(const char);
    
    	int  getnum(void) const;
    	int  getden(void) const;
    	int  getwhole(void) const;
    	char getsign(void) const;
    
    	void display(void) const;
    	void reduce(void) const;

	private:
		char sign;
    	int  whole;
    	int  num;
    	int  den;
    

};


class Problem
{
	
	public:
		Problem();
		
		void setleft(const int);
		void setright(const int);
		
		int getleft(void) const;
		int getright(void) const;
	
		void display (void) const;
		void calculate  (void) const;
	
	private:
		int lefttop;
		int righttop;
		int answer;	 
		
};

class AddProblem : public Problem
{
	public:
		void display (void) const;
		void calculate (void) const;
};

class SubProblem : public Problem
{
	public:
		void display (void) const;
		void calculate (void) const;
};

class MultProblem : public Problem
{
	public:
		void display (void) const;
		void calculate (void) const;
};

class DivProblem : public Problem
{
	public:
		void display (void) const;
		void calculate (void) const;
};

#endif
