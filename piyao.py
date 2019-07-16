import time
import requests
from lxml import etree
from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.keys import Keys
def init_web_driver():
    global driver
    chrome_options = Options()
    # chrome_options.add_argument('--headless')
    chrome_options.add_argument('--disable-gpu')
    driver_path = 'C:\\Users\\Lenovo\\Desktop\\summer1-\\chromedriver.exe'
    driver = webdriver.Chrome(chrome_options=chrome_options, executable_path = driver_path)
browser = webdriver.Chrome()

def close_web_driver():
    driver.quit()

def get_data():
    driver.get('https://piyao.sina.cn')

    while True:
        time.sleep(3)
        driver.execute_script('window.scrollTo(0,1000000)')
        time.sleep(3)
        html = driver.page_source
        html = etree.HTML(html.encode("utf-8", 'ignore'))
        day_dates=driver.find_elements_by_xpath('//div[@class="day_date"]')
        titles=driver.find_elements_by_xpath('//div[@class="left_title"]')
        comments=driver.find_elements_by_xpath('//div[@class="comment_text"]')
        for t in day_dates:
            print(t.text)
        for t in titles:
            print(t.text)
        for t in comments:
            print(t.text)

if __name__ == '__main__':
    init_web_driver()
    get_data()
    close_web_driver()
    