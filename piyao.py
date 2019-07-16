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
    #browser = webdriver.Chrome()

def close_web_driver():
    driver.quit()

def get_data():
    driver.get('https://piyao.sina.cn')
    time.sleep(1)
    js = "return action=document.body.scrollHeight"
    height = driver.execute_script(js)
    driver.execute_script('window.scrollTo(0, document.body.scrollHeight)')
    count=0
    while count<30:
    # 获取当前时间戳（秒）
        t2 = int(time.time())
        t1 = int(time.time())
        # 判断时间初始时间戳和当前时间戳相差是否大于30秒，小于30秒则下拉滚动条
        if t2-t1 < 30:
            new_height = driver.execute_script(js)
            if new_height > height :
                time.sleep(3)
                driver.execute_script('window.scrollTo(0, document.body.scrollHeight)')
                # 重置初始页面高度
                height = new_height
                # 重置初始时间戳，重新计时
                t1 = int(time.time())
        count=count+1
    day_datess=[]
    titless=[]
    commentss=[]
    # html = driver.page_source
    # html = etree.HTML(html.encode("utf-8", 'ignore'))
    day_dates=driver.find_elements_by_xpath('//div[@class="day_date"]')
    for i,day_date in enumerate(day_dates):
        titles=driver.find_elements_by_xpath('//div[@class="zy_day" and position()=%d]/div[@class="day_date"]/following-sibling::ul//div[@class="left_title"]'%(i+1))
        comments=driver.find_elements_by_xpath('//div[@class="zy_day" and position()=%d]/div[@class="day_date"]/following-sibling::ul//div[@class="comment_text"]'%(i+1))
        for t in titles:
            titless.append(t.text)
            day_datess.append(day_date.text)
            #print(day_dates.text,t.text)
        for u in comments:
            commentss.append(u.text)
            #print(t.text)
    #print(infos)

    #titles=driver.find_elements_by_xpath('//div[@class="left_title"]')
    commentss= [ int(x) for x in commentss ]
    the_three= zip(day_datess,commentss,titless)
    the_three= sorted(the_three, key=lambda x : x[1])
    print("最近三个月评论数排名前十的谣言：")
    print('\n')
    for x in the_three[-1:-11:-1]:
        print('日期:', x[0], '题目', x[1],'评论数', x[2])



    # for i in commentss[-1:-11:-1]:
    #     print(i)
    # for i in comments:
    # print(i.text)

if __name__ == '__main__':
    init_web_driver()
    get_data()
    # close_web_driver()
