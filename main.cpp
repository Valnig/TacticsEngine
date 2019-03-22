#include <iostream>
#include <vector>
#include <utility>
#include <sstream>

#define MAX(a,b) ((a) > (b) ? (a) : (b))


class SimpleSpace{
	private: 
	int height_ = 0;
	
	public:
	
	virtual bool walkable() const = 0;
};

class GroundSpace : public SimpleSpace{
	
	
	public :
	
	bool walkable() const {
		return true;
	}
};

class ForestSpace : public  SimpleSpace{
	
	
	public :
	
	bool walkable() const {
		return false;
	}
};

class WaterSpace : public SimpleSpace{
	
	
	public :
	
	bool walkable() const {
		return false;
	}
};


template<typename _SPACE, typename _PAWN>
class Map2D{
	private:
	const int width_;
	const int height_;
	
	protected:
	_SPACE** grid_ = nullptr;
	std::vector<std::pair<int,_PAWN*>> pawns_;///<TODO replace with map
	
	int to_id(int x, int y) const{
		return x*width_ + y;
	}
	//wrong
	void to_coordinates(int id, int& x, int& y) const{
		x = id/width_;
		y = id - x * width_;
	}
	
	int is_occupied(int id) const{
		size_t k(0);
		bool occupied(false);
		
		while(k<pawns_.size() && ! occupied){
			occupied |= pawns_[k].first == id;
			k++;
		}
		return occupied ? (int)k-1 : -1;
	}
	
	public:
	
	Map2D(int width, int height) : width_(MAX(1,width)), height_(MAX(1,height)) {
		grid_ = (_SPACE**) calloc(width_*height_,sizeof(_SPACE*));
	}
	
	~Map2D(){
		free(grid_);
		grid_ = nullptr;
	}
	
	bool add_pawn(_PAWN* pawn, int x, int y){
		if(pawn){
			if(is_occupied(to_id(x,y)) >= 0){
				return false;
			}
			pawns_.push_back({to_id(x,y), pawn});
			return true;
			
		}
		return false;
	}
	
	std::string to_string() const{
		std::stringstream msg;
		
		for(int i(0); i<width_; i++){
			msg<<"|";
			for(int j(0); j<height_;j++){
				
				int occupied = is_occupied(to_id(i,j));
				if(occupied >= 0){
					msg<<pawns_[occupied].second->to_string()<<"|";
				}else if(grid_[to_id(i,j)]){
					//std::cout<<"printing space "<<i<<","<<j<<std::endl;
					msg<<grid_[to_id(i,j)]->to_string()<<"|";
				}else{
					msg<<"XX|";
				}
			}
			msg<<std::endl;
			
			for(int j(0); j<height_;j++){
				msg<<"---";
			}
			msg<<std::endl;
				
		}
		return msg.str();
	}
};
namespace Chess{
	
	typedef enum{PAWN, BISHOP, ROOK, KNIGHT, QUEEN, KING} PIECE_TYPE;
		
	struct Space{	
		const bool color_;///<false : black, true : white
		
		std::string to_string(){
			return color_ ? "##" : "  ";
		}
		
		Space(bool color) : color_(color){}
	};

	class Piece{
		private:
		PIECE_TYPE type_;
		bool color_;
		
		public:
		
		Piece(PIECE_TYPE type, bool color) : type_(type), color_(color){}
		
		static std::string type_to_string(PIECE_TYPE type){
			switch(type){
				case PAWN : return "P";
				case BISHOP : return "B";
				case ROOK : return "R";
				case KNIGHT : return "K";
				case QUEEN : return "Q";
				case KING : return "o";
				default : return "X";
			}
		}
		
		std::string to_string() const {
			return std::string(color_ ? "W" : "B") + type_to_string(type_);
		}
		
	};

	
	class Board : public Map2D<Space, Piece> {
		private:
		
		public:
		
		Board() : Map2D<Space, Piece>(8,8){
			for(int i(0); i<8; i++){
				for(int j(0); j<8; j++){
					grid_[to_id(i,j)] = new Space((i+j)%2);
				}
			}
		}
		
	};

class Game{
	private:
		Board board_;
		
	public:
	
	Game() : board_(){
		
			board_.add_pawn(new Piece(PAWN, false), 1,0);
			board_.add_pawn(new Piece(PAWN, false), 1,1);
			board_.add_pawn(new Piece(PAWN, false), 1,2);
			board_.add_pawn(new Piece(PAWN, false), 1,3);
			board_.add_pawn(new Piece(PAWN, false), 1,4);
			board_.add_pawn(new Piece(PAWN, false), 1,5);
			board_.add_pawn(new Piece(PAWN, false), 1,6);
			board_.add_pawn(new Piece(PAWN, false), 1,7);
			
			board_.add_pawn(new Piece(ROOK, false), 0,0);
			board_.add_pawn(new Piece(KNIGHT, false), 0,1);
			board_.add_pawn(new Piece(BISHOP, false), 0,2);
			board_.add_pawn(new Piece(KING, false), 0,3);
			board_.add_pawn(new Piece(QUEEN, false), 0,4);
			board_.add_pawn(new Piece(BISHOP, false), 0,5);
			board_.add_pawn(new Piece(KNIGHT, false), 0,6);
			board_.add_pawn(new Piece(ROOK, false), 0,7);
			
			board_.add_pawn(new Piece(PAWN, true), 6,0);
			board_.add_pawn(new Piece(PAWN, true), 6,1);
			board_.add_pawn(new Piece(PAWN, true), 6,2);
			board_.add_pawn(new Piece(PAWN, true), 6,3);
			board_.add_pawn(new Piece(PAWN, true), 6,4);
			board_.add_pawn(new Piece(PAWN, true), 6,5);
			board_.add_pawn(new Piece(PAWN, true), 6,6);
			board_.add_pawn(new Piece(PAWN, true), 6,7);
			
			board_.add_pawn(new Piece(ROOK, true), 7,0);
			board_.add_pawn(new Piece(KNIGHT, true), 7,1);
			board_.add_pawn(new Piece(BISHOP, true), 7,2);
			board_.add_pawn(new Piece(KING, true), 7,3);
			board_.add_pawn(new Piece(QUEEN, true), 7,4);
			board_.add_pawn(new Piece(BISHOP, true), 7,5);
			board_.add_pawn(new Piece(KNIGHT, true), 7,6);
			board_.add_pawn(new Piece(ROOK, true), 7,7);
			
	}
	
	std::string to_string() const {
		return board_.to_string();
	}
	
	bool main_loop(){
		int from;
		int to;
		cout<<"what move do you want to do ?"<<std::endl;
		cout<<"enter the piece's location : ";
		cin>>from;
		cout<<"enter the piece's target : ";
		cin>>to;
		
		int x_start = from/10;
		int y_start = from%10;
		int x_end = to/10;
		int y_end = t0%10;
		
		
		
		return false;
	}
	
};

}

using namespace Chess;

int main(){
	
	Game game;
	
	std::cout<<game.to_string()<<std::endl;
	
	while(game.main_loop()){}
	
	return 0;
}
