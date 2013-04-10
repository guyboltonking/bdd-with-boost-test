describe "a stack" do
  let(:stack) { [] }

  context "when initialised" do
    it "should be empty" do
      stack.should be_empty
    end
  end

  describe "pop" do
    context "on an empty stack" do
      before(:each) {
        stack.should be_empty
      }

      it "should have no effect" do
        stack.pop
        stack.should be_empty
      end
    end

    context "on a stack with a single member" do
      before(:each) { 
        stack.push(1) 
        stack.size.should be(1)
      }

      it "should result in an empty stack" do
        stack.pop
        stack.should be_empty
      end

      it "should reduce the stack size by one" do
        expect { stack.pop }.to change { stack.size }.by(-1)
      end
    end

  end

end
