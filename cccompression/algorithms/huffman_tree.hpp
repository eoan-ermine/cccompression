#include <memory>
#include <vector>

namespace eoanermine::cccompression {

struct huff_base_node {
	virtual bool is_leaf() const = 0;
	virtual int weight() const = 0;
};

struct huff_leaf_node : huff_base_node {
	char element;
	int weight_;

	huff_leaf_node(char element, int weight)
		: element(element), weight_(weight) { }

	char value() {
		return element;
	}

	int weight() const override {
		return weight_;
	}

	bool is_leaf() const override {
		return true;
	}
};

struct huff_internal_node : huff_base_node {
	huff_internal_node(std::shared_ptr<huff_base_node> left, std::shared_ptr<huff_base_node> right, int weight)
		: left_(left), right_(right), weight_(weight) { }

	std::shared_ptr<huff_base_node> left() {
		return left_;
	}

	std::shared_ptr<huff_base_node> right() {
		return right_;
	}

	int weight() const override {
		return weight_;
	}

	bool is_leaf() const override {
		return false;
	}
private:
	int weight_;
	std::shared_ptr<huff_base_node> left_;
	std::shared_ptr<huff_base_node> right_;
};

struct huff_tree {
	huff_tree(char element, int weight) {
		root_ = std::make_shared<huff_leaf_node>(element, weight);
	}

	huff_tree(std::shared_ptr<huff_base_node> left, std::shared_ptr<huff_base_node> right, int weight) {
		root_ = std::make_shared<huff_internal_node>(left, right, weight);
	}

	static std::shared_ptr<huff_tree> create() {
		// min heap
		std::vector<std::shared_ptr<huff_tree>> heap;
		std::make_heap(heap.begin(), heap.end(), [](const auto& lhs, const auto& rhs) -> bool {
			return !(lhs->weight() < rhs->weight());
		});

		std::shared_ptr<huff_tree> tmp1, tmp2, tmp3;
		while (heap.size() > 1) {
			std::pop_heap(heap.begin(), heap.end());
			tmp1 = heap.back();
			heap.pop_back();

			std::pop_heap(heap.begin(), heap.end());
			tmp2 = heap.back();
			heap.pop_back();

			tmp3 = std::make_shared<huff_tree>(tmp1->root(), tmp2->root(), tmp1->weight() + tmp2->weight());
		}

		return tmp3;
	}

	std::shared_ptr<huff_base_node> root() const {
		return root_;
	}

	int weight() const {
		return root_->weight();
	}
private:
	std::shared_ptr<huff_base_node> root_;
};

}