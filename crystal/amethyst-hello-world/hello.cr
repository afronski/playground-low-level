require "amethyst/all"

class TestController < Controller
  actions :index

  def index
      html "Hello world! <img src='/assets/amethyst.jpg'>"
  end
end

App.settings.configure do |conf|
  conf.environment = "production"
end

App.routes.draw do
  all  "/", "test#index"
  register TestController
end

app = App.new
app.serve(8080)