#include <iostream>
#include <vector>
#include <utility>

#define MAX(a,b) ((a) > (b) ? (a) : (b))

template<typename _SPACE, typename _PAWN>
class Map2D{
	private:
	int width_=1;
	int height_=1;
	_SPACE* grid_ = nullptr;
	std::vector<std::pair<int,_PAWN*>> pawns_;///<TODO replace with map
	
	int to_id(int x, int y){
		return x*width + y;
	}
	//wrong
	void to_coordinates(int id, int& x, int& y){
		y = id - x*width;
		x = (id-y)/width;
	}
	
	public:
	
	Map2D(int width, int height) {
		width_ = MAX(1, width);
		height_ = MAX(1,height);
		grid_ = (_SPACE*) calloc(width_*height_,sizeof(_SPACE));
	}
	
	~Map2D(){
		free(grid_);
		grid_ = nullptr;
	}
	
	add_pawn(_PAWN* pawn, int x, int y){
		
	}
};

class SimpleSpace{
	private: 
	int height_ = 0;
	SPACE_TYPE type_ = GROUND;
	
	public:
	typedef enum{WATER, GROUND, TREE} SPACE_TYPE;
	
};

namespace Chess{
	struct Space{	
		bool color_;
	}

	class Piece{
		public:
		virtual bool is_move_valid(Position2d start, Position2d end, bool first_turn = false) = 0;
	}

	class Pawn{
		bool is_move_valid(Position2d start, Position2d end, bool first_turn = false){
			
		}
	}
	
	class Board : public Map2D<Space, Piece> {
		private:
		
		public:
	};

class Game{
	private:
		Map2D<Space, Piece> board;
		
	public:
	
	Game() : board(8,8){
		board.add_piece(new Pawn(), 0,1);
	}
	
};

}




     __
  __/  \__
 /  \__/  \
 \__/  \__/
 /  \__/  \
 \__/  \__/
 
 
int main(){
	
	
	
	return 0;
}
