describe "a stack" do
  let(:stack) { [] }

  context "when initialised" do
    it "is empty" do
      expect(stack).to be_empty
    end
  end

  describe "pop" do
    context "on an empty stack" do
      before(:each) {
        expect(stack).to be_empty
      }

      it "has no effect" do
        stack.pop
        expect(stack).to be_empty
      end
    end

    context "on a stack with a single member" do
      before(:each) { 
        stack.push(1)
        expect(stack.size).to be(1)
      }

      it "results in an empty stack" do
        stack.pop
        expect(stack).to be_empty
      end

      it "reduces the stack size by one" do
        expect { stack.pop }.to change { stack.size }.by(-1)
      end
    end

  end

end
